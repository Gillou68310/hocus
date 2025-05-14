import ida_segment
import idautils
import ida_offset
import ida_ua
import idc
import ida_funcs

BP = 6 #Stack var register

def plain_offset_next_insn(head, seg_ea, end_ea, r):
    if r == 10:
        return False
    
    insn = ida_ua.insn_t()
    ida_ua.decode_insn(insn, head)
    next_head = head+insn.size

    #Stop at call
    if('call' in idc.GetDisasm(head)):
        return False
    
    #Stop at end function
    if next_head >= end_ea:
        return False

    if insn.ops[1].type == ida_ua.o_imm:
        if('push' in idc.GetDisasm(next_head)):
            ida_offset.op_plain_offset(head, 1, seg_ea)
            return True
        elif('jmp' in idc.GetDisasm(next_head)):
            #Follow branch
            i = ida_ua.insn_t()
            ida_ua.decode_insn(i, next_head)
            off = i.ops[0].addr - i.ip
            if('push' in idc.GetDisasm(next_head+off)):
                ida_offset.op_plain_offset(head, 1, seg_ea)
                return True
            #Stop if no push at branch target
            return False
    
    return plain_offset_next_insn(next_head, seg_ea, end_ea, r+1)

#TODO: push after imm assign should match the register
dseg = ida_segment.get_segm_by_name('dseg')
prev_head = 0
for seg_ea in idautils.Segments():
    seg = ida_segment.getseg(seg_ea)
    seg_name = ida_segment.get_segm_name(seg)
    if seg_name == 'seg000':
        continue
    if seg_name == 'seg014':
        break
    for head in idautils.Heads(seg.start_ea, seg.end_ea):
        inst = idc.GetDisasm(head)
        insn = ida_ua.insn_t()
        inslen = ida_ua.decode_insn(insn, head)
        if insn.ops[0].type == ida_ua.o_displ and insn.ops[0].reg != BP and ':' not in inst:
            ida_offset.op_plain_offset(head, 0, dseg.start_ea)
        elif insn.ops[1].type == ida_ua.o_displ and insn.ops[1].reg != BP and ':' not in inst:
            ida_offset.op_plain_offset(head, 1, dseg.start_ea)
        elif inst.split() == ['push', 'ds']:
            prev_insn = ida_ua.insn_t()
            ida_ua.decode_insn(prev_insn, prev_head)
            f = ida_funcs.get_func(head)

            if prev_insn.ops[1].type == ida_ua.o_imm and ('push' in idc.GetDisasm(head+insn.size)):
                ida_offset.op_plain_offset(prev_head, 1, dseg.start_ea)
            elif plain_offset_next_insn(head+insn.size, dseg.start_ea, f.end_ea, 0):
                pass
            else:
                print(seg_name+":"+"{:04X}".format(insn.ip))

        prev_head = head