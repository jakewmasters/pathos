;=====================
; pathos bootloader
; by jake masters
;=====================

; run in 16-bit real mode
; load at 0x7c00
; both nasm specific
bits 16
org 0x7c00 ; i think this is a segment:offset address


; starting point
start: jmp loader

; helper stuff to be called by loader
msg db "Welcome!", 0

print:
    lodsb 
    or    al, al
    jz    done
    mov   ah, 0x0e
    int   0x10      ; video interrupt
    jmp   print
done:
    ret

; do some cool stuff
; 
; clear interrupt flag
; enter halt state
loader:
    xor  ax, ax
    mov  ds, ax
    mov  es, ax
    mov  si, msg
    call print
    xor  ax, ax
    int  0x12

    cli
    hlt

; final bootloader touches
; set first 510 bytes to 0
; put magic numbers in last two bytes
; all nasm pseudo-instructions
times 510-($-$$) db 0
dw 0xAA55
