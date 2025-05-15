IDEAL

public _MCPY

segment SEG012 byte public 'CODE' use16
assume cs:SEG012

proc            _MCPY far

dst             = dword ptr  6
src             = dword ptr  0Ah
size            = word ptr  0Eh

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
endp            _MCPY

ends SEG012

END