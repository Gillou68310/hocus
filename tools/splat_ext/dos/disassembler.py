from splat.segtypes.common.asm import CommonSegAsm
from splat.segtypes.common.data import CommonSegData
from splat.segtypes.common.codesubsegment import CommonSegCodeSubsegment
from splat.util import options
from pathlib import Path
import regex as re
import struct

import ida_idaapi
import ida_struct
import ida_bytes
import idautils
import idaapi
import ida_ua
import idc

x86_reg = re.compile(r"\b((?:(?:[sd]i|[sb]p)|[abcd][xhl]))\b(?![:\]])")
comments = re.compile(r"( +;.*\n +;.*)|( +;.*)|((?<=.);.*)|(;.*\n)")
segments = re.compile(r".*\bassume\b.*\n|.*\bsegment\b.*\n|.*\bends\b.*\n")
newline = re.compile(r"\\\n+\s+(.*)")
reserved = re.compile(r"(?<=\n|^|\+|-|\.)([Oo]ffset|[Tt]ype|[Nn]ame|[Aa]ddr|[Pp]age|[Mm]ask|c|[Ll]ength|ptr|st|str|[Ww]ord|[Ww]ait|ne|[Vv]ersion|[Ee]xitcode|dp|[Rr]adix|[Ss]ize|[Ee]nd|[Ww]idth|[Tt]his)\b")
label = re.compile(r"(loc|def|jpt|locret)_[0-9:A-F]+")
generated = re.compile(r"((sub|byte|word|dword)_[0-9:A-F]+)")
jwasm = "jwasm" in options.opts.asm_path.as_posix()
proto = "proto" in options.opts.asm_path.as_posix()

def get_segment_symbols(segment: CommonSegCodeSubsegment) -> list:
    syms = []
    for ea in idautils.Heads(segment.vram_start, segment.vram_end):
        sym = idaapi.get_name(ea)
        if sym != "":
            syms.append(sym)
    return syms

def get_struct_from_addr(addr) -> str:
    i = 0
    for ref in idautils.XrefsFrom(addr):
        s = ida_struct.get_struc_name(ref.to)
        i += 1
    assert(i == 1)
    return s

def get_type_from_addr(addr) -> str:
    flags = ida_bytes.get_flags(addr)
    if ida_bytes.is_byte(flags):
        return "byte"
    elif ida_bytes.is_word(flags):
        return "word"
    elif ida_bytes.is_dword(flags):
        return "dword"
    elif ida_bytes.is_struct(flags):
        return get_struct_from_addr(addr)
    elif ida_bytes.is_float(flags):
        return "dword"
    elif ida_bytes.is_strlit(flags):
        return "byte"
    elif ida_bytes.is_func(flags):
        return "far"
    else:
        assert(0)

def externdef(ref, sym: str) -> str:
    extern = "extrn "
    if re.match(generated, sym):
        extern += "_"
    if ref.type  == idc.fl_CF:
        return extern + sym + ":far\n"
    elif ref.type  == idc.fl_CN:
        return extern + sym + ":near\n"
    else:
        addr = idaapi.get_name_ea(0, sym)
        t = get_type_from_addr(addr)
        return extern + sym + ":" + t + "\n"
    
def get_subsegment_from_addr(segment: CommonSegCodeSubsegment, addr) -> CommonSegCodeSubsegment:
    for subsegments in segment.parent.subsegments:
        if subsegments.vram_start == None or subsegments.vram_end == None:
            continue
        if addr >= subsegments.vram_start and addr < subsegments.vram_end:
            return subsegments
    return None

def resolve_external_refs(segment: CommonSegAsm, data_sym: list) -> str:
    syms = set()
    out = ""
    for ea in idautils.Heads(segment.vram_start, segment.vram_end):
        sym = idaapi.get_name(ea)
        if not jwasm:
            #Mark segment functions as public
            if sym != "" and not re.match(label, sym):
                if re.match(generated, sym):
                    out += "public _" + sym + "\n"
                else:
                    out += "public " + sym + "\n"

        for ref in idautils.XrefsFrom(ea):
            sym = idaapi.get_name(ref.to)
            subsegment = get_subsegment_from_addr(segment, ref.to)
            #Addend or struct.member
            if sym == "" and subsegment != None and subsegment.is_data():
                disa = idc.GetDisasm(ea)
                if "." in disa:
                    sym = disa.split(".")[0].split()[-1]
                elif "+" in disa:
                    sym = disa.split("+")[0].split()[-1]
                sym = re.sub("[\[\()]", "", sym)
                addr = idaapi.get_name_ea(ea, sym)
                assert(get_subsegment_from_addr(segment, addr).is_data())
            if sym == "":
                continue
            #Symbol already defined in data segment
            if sym in data_sym:
                continue
            #Symbol already defined in current segment
            if subsegment != None and subsegment is segment:
                continue
            if re.match(label, sym):
                assert(0)
            if sym not in syms:
                syms.add(sym)
                out += externdef(ref, sym)
    return out+"\n"

def disasm_types(path: Path) -> str:
    idc.gen_file(idc.OFILE_ASM, path.absolute().as_posix(), 0, ida_idaapi.BADADDR, idc.GENFLG_ASMINC|idc.GENFLG_ASMTYPE)
    with path.open("r") as f:
        types = f.read()
        types = re.sub(comments, "", types)
        types = re.sub(reserved,  r"_\1", types)
        types = re.sub(newline, r"\1", types)
        #Struct member is struct type
        types = re.sub(r"(?<! d[bwd] )\?\n", r"<?>\n", types)
    return types

def disasm_data(path: Path, segment: CommonSegData) -> str:
    idc.gen_file(idc.OFILE_ASM, path.absolute().as_posix(), segment.vram_start, segment.vram_end, 0)
    with path.open("r") as f:
        data = f.read()
        data = re.sub(comments, r"", data)
        data = re.sub(segments, r"", data)
        data = re.sub(newline, r"\1", data)
        data = re.sub(generated, r"_\1", data)
        if segment.type == 'bss':
            data = re.sub(r"(0.0|0)(?=[\n>\)])", r"?", data)
    return datasegment(segment.type, get_align(segment), data)

def disasm_code(path: Path, segment: CommonSegAsm) -> str:
    pa = Patch(segment, jwasm)
    pa.apply_patch()
    idc.gen_file(idc.OFILE_ASM, path.absolute().as_posix(), segment.vram_start, segment.vram_end, 0)
    pa.revert_patched_bytes()

    with path.open("r") as f:
        disasm = f.read()
        disasm = re.sub(comments, r"", disasm)
        disasm = re.sub(reserved, r"_\1", disasm)
        disasm = re.sub(segments, r"", disasm)
        disasm = re.sub(newline, r"\1", disasm)
        disasm = re.sub(generated, r"_\1", disasm)
        disasm = re.sub(r"call(?!\s+(near|\[))\s+", r"call    far ptr ", disasm)
        #Replace segment name by symbol name
        disasm = re.sub(r"(seg\s+)(.*)(\n.*offset\s+)(.*)", r"\1\4\3\4", disasm)
        if jwasm:
            disasm = re.sub(r"seg dseg", r"seg _DATA", disasm)
            #Move function end after jpt
            disasm = re.sub(r"(\n.*endp)(\n*(.*d[wb] .*\n)+)", r"\2\1\n", disasm)
            #FP fixups for 16-bit code. These fixups allow the linker
            #or program loader to replace FP instructions by calls to an FP emulation
            #library.
            disasm = re.sub(r"\swait\n", r" nop\n                wait\n", disasm)
            disasm = re.sub(r"\sfnstsw\s", r" fstsw  ", disasm)
        else:
            disasm = re.sub(r"seg dseg", r"seg _DATA:0", disasm)
            disasm = re.sub(r"\swait\n", r" fwait\n", disasm)
            disasm = re.sub(r"\sfnstsw\s", r" fstsw  ", disasm)
            #Parenthesis around struct.member
            disasm = re.sub(r"([^ ([]+\.[^ \+\-\]\n]+)", r"(\1)", disasm)
            #Manual relocs to TASM ideal
            disasm = re.sub(r"([^ ]+)\[bx\]", r"[\1+bx]", disasm)

        return codesegment(segment, disasm)

def resolve_public_symbols(symbols: list) -> str:
    public = ""
    for sym in symbols:
        if re.match(generated, sym):
            sym = "_" + sym
        if sym[0] == "_":
            public += "public " + sym + "\n"
    return public+"\n"

def get_align(segment: CommonSegCodeSubsegment) -> str:
    if segment.align != None:
        if segment.align == 1:
            return "byte"
        elif segment.align == 2:
            return "word"
    return "word"

def codesegment(segment: CommonSegAsm, disasm: str) -> str:
    out = ""
    if jwasm:
        out += "DGROUP GROUP _DATA,_BSS\n\n"
        out += "DOS_SRC_TEXT" + " segment " + get_align(segment) + " public 'CODE' use16\n"
        out += "assume cs:" + "DOS_SRC_TEXT" + ", ss:DGROUP, ds:DGROUP\n\n"
        out += disasm
        out += "DOS_SRC_TEXT" + " ends\n\n"
    else:
        segname = segment.name.split('/')[-1].upper()
        out += "GROUP DGROUP _DATA,_BSS\n\n"
        out += "segment " + segname + " " + get_align(segment) + " public 'CODE' use16\n"
        out += "assume cs:" + segname + ", ss:DGROUP, ds:DGROUP\n\n"
        out += disasm
        out += "ends " + segname + "\n\n"
    return out

def datasegment(type: str, align: str, data: str) -> str:
    out = ""
    if jwasm:
        out += "_" + type.upper() + " segment " + align + " public '" + type.upper() + "'\n"
        out += data
        out += "_" + type.upper() + " ends\n"
    else:
        out += "segment _" + type.upper() + " " + align + " public '" + type.upper() + "'\n"
        out += data
        out += "ends _" + type.upper() + "\n"
    return out

def get_subsegment(segment: CommonSegCodeSubsegment, type) -> CommonSegCodeSubsegment:
    for subsegments in segment.parent.subsegments:
        if subsegments.name == segment.name and subsegments.type == type:
            return subsegments
    return None

def disassemble_data(segment: CommonSegData):   
    if jwasm or get_subsegment(segment, "asm") != None:
        return
    
    path = segment.out_path()
    path.parent.mkdir(parents=True, exist_ok=True)
    types = disasm_types(path)
    public = resolve_public_symbols(get_segment_symbols(segment))
    data = disasm_data(path, segment)
    with path.open("w") as f:
        f.write("IDEAL\n\n"+types+public+data+"END")
        
def disassemble_code(segment: CommonSegAsm):
    path = segment.out_path()
    path.parent.mkdir(parents=True, exist_ok=True)

    data_syms = []
    data = ""
    for type in ["data", "bss"]:
        subsegment = get_subsegment(segment, type)
        if subsegment != None and not jwasm:
            data_syms += get_segment_symbols(subsegment)
            data += disasm_data(path, subsegment) + "\n"
        else:
            data += datasegment(type, "word", "") + "\n"

    types = disasm_types(path)
    publics = resolve_public_symbols(data_syms)            
    refs = resolve_external_refs(segment, data_syms)
    disasm = disasm_code(path, segment)

    with path.open("w") as f:
        if jwasm:
            if not proto:
                f.write(".286\n")
            f.write(".MODEL LARGE\n\n")
        else:
            if not proto:
                f.write("P286\n")
            f.write("IDEAL\n\n")

        f.write(types+publics+refs+data+disasm+"END")

class Patch():
    def __init__(self, segment: CommonSegAsm, jwasm):
        self.patch = []
        self.segment = segment
        self.jwasm = jwasm
            
    def apply_patch(self):
        for ea in idautils.Heads(self.segment.vram_start, self.segment.vram_end):
            disasm = idc.GetDisasm(ea)
            inst = disasm.split()
            if "call" in inst[0] and "near" in inst[1]:
                self._patch_far_to_near_call(ea)
                continue
            elif "jmp" in inst[0]:
                self._patch_near_to_short_jmp(ea)
                continue
            elif "and" in inst[0] or "or" in inst[0]:
                if self._patch_sign_extended(ea):
                    continue
            
            self._patch_inline_asm(disasm, ea)

    def _patch_near_to_short_jmp(self, ea):
        #Jwasm is using short jmp (EB cb) when jump offset equal 127 but TASM is using near jmp (E9 cw)
        if not self.jwasm:
            return
        
        insn = ida_ua.insn_t()
        inslen = ida_ua.decode_insn(insn, ea)
        offset = insn.ops[0].addr - (insn.ip+insn.size)
        if offset != 127:
            return
        
        assert(insn.size == 3)
        print("Patched near to short jmp at: "+self.segment.name+":"+"{:04X}".format(insn.ip))
        self.patch.append((ea, idaapi.get_bytes(ea, 3)))
        ida_bytes.del_items(ea, 0, 3)

    def _patch_far_to_near_call(self, ea):
        #Far calls are patched to near calls at link time if called function
        #is defined in the same TU
        if not self.jwasm:
            return False
        
        insn = ida_ua.insn_t()
        inslen = ida_ua.decode_insn(insn, ea)
        if insn.ops[0].addr <= insn.ip:
            return False

        prev = idc.GetDisasm(ea-2)
        if not "nop" in prev:
            return False

        prev = idc.GetDisasm(ea-1).split()
        if not ("push" in prev[0]):
            return False

        if not ("cs" in prev[1]):
            return False
        
        print("Patched far to near call at: "+self.segment.name+":"+"{:04X}".format(insn.ip))
        self.patch.append((ea-2, idaapi.get_bytes(ea-2, 1)))
        self.patch.append((ea-1, idaapi.get_bytes(ea-1, 1)))
        self.patch.append((ea, idaapi.get_bytes(ea, 3)))
        packed = struct.pack("<BHH", 0x9A, insn.ops[0].addr, self.segment.vram_start>>4)
        idaapi.patch_bytes(ea-2,packed)
        return True

    def _patch_inline_asm(self, disasm, ea):
        #Inline asm uses r/m,r instead of r,r/m opcode when both operands are gprs
        if self.jwasm:
            return False
        
        insn = ida_ua.insn_t()
        inslen = ida_ua.decode_insn(insn, ea)
        if insn.size != 2:
            return False
        
        result = x86_reg.findall(disasm)
        if len(result) != 2:
            return False
        
        data = idaapi.get_bytes(ea, 2)
        if  (data[0] & 2) != 0:
            return False
        
        print("Patched inline asm: "+self.segment.name+":"+"{:04X}".format(insn.ip))
        self.patch.append((ea, data))
        ida_bytes.del_items(ea, 0, 2)
        return True

    def _patch_sign_extended(self, ea):
        #TASM generate sign extended for AND/OR r/m16, imm16
        if self.jwasm:
            return False
        
        insn = ida_ua.insn_t()
        inslen = ida_ua.decode_insn(insn, ea)
        
        data = idaapi.get_bytes(ea, insn.size)
        if data[0] != 0x81:
            return False
        
        print("Patched sign extended: "+self.segment.name+":"+"{:04X}".format(insn.ip))
        self.patch.append((ea, data))
        ida_bytes.del_items(ea, 0, insn.size)
        return True

    def revert_patched_bytes(self):
        for ea, data in self.patch:
            idaapi.patch_bytes(ea, data)
            ida_ua.create_insn(ea)
        
        self.patch.clear()
        