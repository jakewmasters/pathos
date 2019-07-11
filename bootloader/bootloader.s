; PathOS bootloader
; by Jake Masters

[org 0x7c00]
[bits 16]

start:
    jmp start

sign:
    times 510-($-$$) db 0
    dw 0xaa55


; ^^ necessary stuff ^^
; stuff below is extra

; prints whatever is in al
print_char:
    pusha
    mov ah, 0x0e
    int 0x10
    popa
    ret
