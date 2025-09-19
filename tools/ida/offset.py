import ida_segment
import ida_offset
import ida_funcs
import idautils
import ida_ua
import idaapi
import idc

BP = 6 #Stack var register
DS = 32 #data seg register

def plain_offset_prev_insn(insn, next_head, prev_head, seg_ea):
    #Already an offset
    if('offset' in idc.GetDisasm(prev_head)):
        return True
    
    next_insn = ida_ua.insn_t()
    ida_ua.decode_insn(next_insn, next_head)
    
    prev_insn = ida_ua.insn_t()
    ida_ua.decode_insn(prev_insn, prev_head)

    if prev_insn.ops[1].type == ida_ua.o_imm:
        if insn != None and next_insn.ops[0].addr+2 == insn.ops[0].addr:
            ida_offset.op_plain_offset(prev_head, 1, seg_ea)
            return True

        if('push' in idc.GetDisasm(next_head)):
            dreg = idc.GetDisasm(prev_head).split()[1].split(',')[0].split(';')[0]
            sreg = idc.GetDisasm(next_head).split()[1].split(',')[0].split(';')[0]
            if dreg == sreg:
                ida_offset.op_plain_offset(prev_head, 1, seg_ea)
                return True
            
    return False

def plain_offset_next_insn(insn, next_head, seg_ea, end_ea, r):
    if r == 10:
        return False
    
    next_insn = ida_ua.insn_t()
    ida_ua.decode_insn(next_insn, next_head)
    next_head2 = next_head+next_insn.size

    #Already an offset
    if('offset' in idc.GetDisasm(next_head)):
        return True
    
    #Stop at call
    if('call' in idc.GetDisasm(next_head)):
        return False
    
    #Stop at end function
    if next_head2 >= end_ea:
        return False

    if next_insn.ops[1].type == ida_ua.o_imm:
        if insn != None and next_insn.ops[0].addr+2 == insn.ops[0].addr:
            ida_offset.op_plain_offset(next_head, 1, seg_ea)
            return True
        
        dreg = idc.GetDisasm(next_head).split()[1].split(',')[0].split(';')[0]
        if('push' in idc.GetDisasm(next_head2)):
            sreg = idc.GetDisasm(next_head2).split()[1].split(',')[0].split(';')[0]
            if dreg == sreg:
                ida_offset.op_plain_offset(next_head, 1, seg_ea)
                return True
        elif('jmp' in idc.GetDisasm(next_head2)):
            #Follow branch
            i = ida_ua.insn_t()
            ida_ua.decode_insn(i, next_head2)
            off = i.ops[0].addr - i.ip
            if('push' in idc.GetDisasm(next_head2+off)):
                sreg = idc.GetDisasm(next_head2+off).split()[1].split(',')[0].split(';')[0]
                if dreg == sreg:
                    ida_offset.op_plain_offset(next_head, 1, seg_ea)
                    return True
            #Stop if no push at branch target
            return False
    
    return plain_offset_next_insn(None, next_head2, seg_ea, end_ea, r+1)

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
            if plain_offset_prev_insn(insn, head+insn.size, prev_head, dseg.start_ea):
                pass
            elif plain_offset_next_insn(insn, head+insn.size, dseg.start_ea, f.end_ea, 0):
                pass
            else:
                print(seg_name+":"+"{:04X}".format(insn.ip))
        elif inst.split() == ['push', 'ds']:
            if plain_offset_prev_insn(None, head+insn.size, prev_head, dseg.start_ea):
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