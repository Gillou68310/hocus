IDEAL

public _MCPY

segment MEMCPY byte public 'CODE' use16
assume cs:MEMCPY

proc _MCPY far

dst  = dword ptr  6
src  = dword ptr  0Ah
size = word ptr  0Eh

    push    bp
    mov     bp, sp
    push    ds
    push    es
    push    si
    push    di
    les     di, [bp+dst]
    lds     si, [bp+src]
    mov     cx, [bp+size]
    rep movsb
    pop     di
    pop     si
    pop     es
    pop     ds
    mov     sp, bp
    pop     bp
    retf

endp _MCPY

ends MEMCPY

END