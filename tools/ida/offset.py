import ida_segment
import ida_offset
import ida_funcs
import idautils
import ida_ua
import idaapi
import idc

BP = 6 #Stack var register
DS = 32 #data seg register

def plain_offset_prev_insn(head, prev_head, seg_ea):
    #Already an offset
    if('offset' in idc.GetDisasm(prev_head)):
        return True
    
    prev_insn = ida_ua.insn_t()
    ida_ua.decode_insn(prev_insn, prev_head)
    if prev_insn.ops[1].type == ida_ua.o_imm:
        dreg = idc.GetDisasm(prev_head).split()[1].split(',')[0].split(';')[0]
        if('push' in idc.GetDisasm(head)):
            sreg = idc.GetDisasm(head).split()[1].split(',')[0].split(';')[0]
            if dreg == sreg:
                ida_offset.op_plain_offset(prev_head, 1, seg_ea)
                return True
            
    return False

def plain_offset_next_insn(previous_insn, head, seg_ea, end_ea, r):
    if r == 10:
        return False
    
    insn = ida_ua.insn_t()
    ida_ua.decode_insn(insn, head)
    next_head = head+insn.size

    #Already an offset
    if('offset' in idc.GetDisasm(head)):
        return True
    
    #Stop at call
    if('call' in idc.GetDisasm(head)):
        return False
    
    #Stop at end function
    if next_head >= end_ea:
        return False

    if insn.ops[1].type == ida_ua.o_imm:
        if previous_insn != None and insn.ops[0].addr+2 == previous_insn.ops[0].addr:
            ida_offset.op_plain_offset(head, 1, seg_ea)
            return True
        dreg = idc.GetDisasm(head).split()[1].split(',')[0].split(';')[0]
        if('push' in idc.GetDisasm(next_head)):
            sreg = idc.GetDisasm(next_head).split()[1].split(',')[0].split(';')[0]
            if dreg == sreg:
                ida_offset.op_plain_offset(head, 1, seg_ea)
                return True
        elif('jmp' in idc.GetDisasm(next_head)):
            #Follow branch
            i = ida_ua.insn_t()
            ida_ua.decode_insn(i, next_head)
            off = i.ops[0].addr - i.ip
            if('push' in idc.GetDisasm(next_head+off)):
                sreg = idc.GetDisasm(next_head+off).split()[1].split(',')[0].split(';')[0]
                if dreg == sreg:
                    ida_offset.op_plain_offset(head, 1, seg_ea)
                    return True
            #Stop if no push at branch target
            return False
    
    return plain_offset_next_insn(None, next_head, seg_ea, end_ea, r+1)

import debugpy
debugpy.listen(("localhost", 5678),in_process_debug_adapter=True)
debugpy.wait_for_client()

dseg = ida_segment.get_segm_by_name('dseg')
prev_head = 0
for seg_ea in idautils.Segments():
    seg = ida_segment.getseg(seg_ea)
    seg_name = ida_segment.get_segm_name(seg)
    if seg_name == 'seg000':
        continue
    if seg_name == 'seg025':
        break
    for head in idautils.Heads(seg.start_ea, seg.end_ea):
        inst = idc.GetDisasm(head)
        insn = ida_ua.insn_t()
        inslen = ida_ua.decode_insn(insn, head)
        f = ida_funcs.get_func(head)

        if insn.ops[0].type == ida_ua.o_displ and insn.ops[0].reg != BP and ':' not in inst:
            ida_offset.op_plain_offset(head, 0, dseg.start_ea)
        elif insn.ops[1].type == ida_ua.o_displ and insn.ops[1].reg != BP and ':' not in inst:
            ida_offset.op_plain_offset(head, 1, dseg.start_ea)
        elif insn.ops[0].type == ida_ua.o_displ and insn.ops[1].type == ida_ua.o_reg and insn.ops[1].reg == DS:
            plain_offset_next_insn(insn, head+insn.size, dseg.start_ea, f.end_ea, 0)
        elif inst.split() == ['push', 'ds']:
            if plain_offset_prev_insn(head+insn.size, prev_head, dseg.start_ea):
                pass
            elif plain_offset_next_insn(None, head+insn.size, dseg.start_ea, f.end_ea, 0):
                pass
            else:
                print(seg_name+":"+"{:04X}".format(insn.ip))

        prev_head = head

#Cleanup orphaned local names
for seg_ea in idautils.Segments():
    seg = ida_segment.getseg(seg_ea)
    for head in idautils.Heads(seg.start_ea, seg.end_ea):
        sym = idaapi.get_name(head)
        if sym.startswith("loc_") or sym.startswith("locret_"):
            idaapi.set_name(head, "")