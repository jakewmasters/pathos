;=============================
; PathOS bootloader - stage 0
; by Jake Masters
;=============================

bits 16

org 0x7c00

start:
    jmp sign

sign:
    times 510-($-$$) db 0
    dw 0xaa55