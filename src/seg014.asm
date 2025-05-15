IDEAL

public _SET320X200

segment SEG014 word public 'CODE' use16
assume cs:SEG014

proc            _SET320X200 far
                push    bp
                mov     bp, sp
                push    si
                push    di
                mov     ax, 13h
                int     10h
                mov     dx, 3C4h
                mov     al, 4
                out     dx, al
                inc     dx
                in      al, dx
                and     al, 0F7h
                or      al, 4
                out     dx, al
                mov     dx, 3CEh
                mov     al, 5
                out     dx, al
                inc     dx
                in      al, dx
                and     al, 0EFh
                out     dx, al
                dec     dx
                mov     al, 6
                out     dx, al
                inc     dx
                in      al, dx
                and     al, 0FDh
                out     dx, al
                mov     dx, 3C4h
                mov     ax, 0F02h
                out     dx, ax
                mov     ax, 0A000h
                mov     es, ax
                sub     di, di
                mov     ax, di
                mov     cx, 8000h
                cld
                rep stosw
                mov     dx, 3D4h
                mov     al, 9
                out     dx, al
                inc     dx
                in      al, dx
                mov     al, 1
                out     dx, al
                dec     dx
                mov     al, 14h
                out     dx, al
                inc     dx
                in      al, dx
                and     al, 0BFh
                out     dx, al
                dec     dx
                mov     al, 17h
                out     dx, al
                inc     dx
                in      al, dx
                or      al, 40h
                out     dx, al
                pop     di
                pop     si
                pop     bp
                retf
endp            _SET320X200

ends SEG014

END