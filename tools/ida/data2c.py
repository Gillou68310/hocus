from pathlib import Path
from splat.scripts import split
from splat.segtypes.common.data import CommonSegData

import idaapi
import idc
import idautils
import ida_bytes
import ida_struct
import ida_typeinf
import ctypes

def export_struct_member(f, sid, union, ea, m):
    flags = idc.get_member_flag(sid, m.soff)
    assert(flags != -1)

    #TODO: this probably won't work for multi-dimensional arrays
    ti = ida_typeinf.tinfo_t()
    idaapi.get_member_type(m, ti)
    dim = []
    count = 1
    if ti.is_array():
        count = ti.get_array_nelems()
        dim.append(count)

    member_sid = None
    if ida_bytes.is_struct(flags):
        member_sid = idc.get_member_strid(sid, m.soff)

    member = ea
    if not union:
        member += m.soff

    size = ida_struct.get_member_size(m)
    export_data_from_addr(f, member, size, flags, member_sid, dim, ti.is_signed(), False)

def export_struct(f, ea, sid):
    union = ida_struct.is_union(sid)
    struct_size = ida_struct.get_struc_size(sid)
    f.write("{")
    sptr = ida_struct.get_struc(sid)
    i = 0
    for m in sptr.members:
        export_struct_member(f, sid, union, ea, m)
        if i != sptr.members.count-1:
            f.write(", ")
        i += 1
    f.write("}")
    return struct_size

def get_struct_from_addr(addr):
    i = 0
    for ref in idautils.XrefsFrom(addr):
        s = ida_struct.get_struc_name(ref.to)
        i += 1
    assert(i == 1)
    return ida_struct.get_struc_id(s)

def get_decl(ea):
    name = idaapi.get_name(ea)
    if name == None:
        return None
    
    if name[0] != "_":
        return None
    
    ty = idc.get_type(ea)
    if ty == None:
        return None
    
    ty = ty.replace("__int8", "char")
    if "[" in ty:
        s = ty.split("[", 1)
        return s[0] + " " + name[1:] + "[" + s[1]
    else:
        return ty + " " + name[1:]
    
def get_array_dim(ea):
    ty = idc.get_type(ea)
    if ty == None:
        return None
    
    dim = []
    ss = ty.split("[")
    ss = ss[1:]
    for s in ss:
        d = int(s.split("]")[0])
        dim.append(d)
    return dim

def is_signed(ea):
    ty = idc.get_type(ea)
    if ty == None:
        return False
    
    if "unsigned" in ty or "*" in ty:
        return False
    else:
        return True

def export_data(f, ea, flags, sid, signed):
    newline = False
    if ida_bytes.is_byte(flags):
        data = ida_bytes.get_byte(ea)
        if signed: f.write(str(ctypes.c_int8(data).value))
        else: f.write(hex(data))
        return 1,newline
    elif ida_bytes.is_word(flags):
        data = ida_bytes.get_16bit(ea)
        if signed: f.write(str(ctypes.c_int16(data).value))
        else: f.write(hex(data))
        return 2,newline
    elif ida_bytes.is_dword(flags):
        data = ida_bytes.get_32bit(ea)
        addr = (data >> 16) * 0x10 + (data & 0xFFFF)
        flags = ida_bytes.get_flags(addr)
        if ida_bytes.is_strlit(flags):
            s = ida_bytes.get_strlit_contents(addr, -1, -1)
            f.write('"'+s.decode("utf-8")+'"')
            newline = True
        else:
            name = idaapi.get_name(addr)
            if name != "":
                f.write(name)
            else:
                f.write(hex(data))
        return 4,newline
    elif ida_bytes.is_struct(flags):
        stru_size = export_struct(f, ea, sid)
        newline = True
        return stru_size,newline
    elif ida_bytes.is_float(flags):
        assert(0)
    elif ida_bytes.is_strlit(flags):
        s = ida_bytes.get_strlit_contents(ea, -1, -1)
        f.write('"'+s.decode("utf-8")+'"')
        return len(s),newline
    else:
        assert(0)

def export_array(f, ea, flags, dim, sid, signed):
    for i in range(0, dim[0]):
        if len(dim) > 1:
            f.write("{")
            ea = export_array(f, ea, flags, dim[1:], sid, signed)
            f.write("}")
            if i != dim[0]-1:
                f.write(",\n")
        else:
            size, newline = export_data(f, ea, flags, sid, signed)
            ea += size
            if i != dim[0]-1:
                if newline:
                    f.write(",\n")
                else:
                    f.write(", ")
    return ea

def export_data_from_addr(f, ea, size, flags, sid, dim, signed, newline):
    count = 1
    for d in dim:
        count *= d

    if ida_bytes.is_byte(flags):
        assert(size == count)
    elif ida_bytes.is_word(flags):
        assert((size % 2) == 0)
        assert(size == count*2)
    elif ida_bytes.is_dword(flags):
        assert((size % 4) == 0)
        assert(size == count*4)
    elif ida_bytes.is_struct(flags):
        struct_size = ida_struct.get_struc_size(sid)
        assert((size % struct_size) == 0)
        assert(size == count*struct_size)
    elif ida_bytes.is_float(flags):
        assert(0)
    elif ida_bytes.is_strlit(flags):
        pass
    else:
        assert(0)

    if len(dim) != 0:
        f.write("{")
        if newline: f.write("\n")
        export_array(f, ea, flags, dim, sid, signed)
        if newline: f.write("\n")
        f.write("}")
    else:
        export_data(f, ea, flags, sid, signed)

def export_segment_data(f, segment: CommonSegData):
    for ea in range(segment.vram_start, segment.vram_end):
        if idaapi.get_name(ea) != "":
            decl = get_decl(ea)
            if decl != None:
                f.write(decl + " = ")
                flags = ida_bytes.get_flags(ea)
                sid = None
                if ida_bytes.is_struct(flags):
                    sid = get_struct_from_addr(ea)
                dim = get_array_dim(ea)
                size = ida_bytes.get_item_size(ea)
                export_data_from_addr(f, ea, size, flags, sid, dim, is_signed(ea), True)
                f.write(";\n\n")

import debugpy
debugpy.listen(("localhost", 5678),in_process_debug_adapter=True)
debugpy.wait_for_client()

VERSION = "proto"
path =  Path("versions") / VERSION / "hocus.yaml"
config = split.conf.load([path])

split.options.opts.platform = "dos" #TODO
out_path = Path("data")
out_path.mkdir(parents=True, exist_ok=True)
all_segments = split.initialize_segments(config["segments"])

for segment in all_segments:
    if segment.name == "code":
        break

for subsegment in segment.subsegments:
    if subsegment.type == "data":
        path = out_path / (subsegment.name + ".c")
        with path.open("w") as f:
            export_segment_data(f, subsegment)
