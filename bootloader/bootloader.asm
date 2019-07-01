; another sample bootloader
; by Jake Masters

org 0x7c00
bits 16

start:
    jmp boot

boot:
    cli
    cld    ; need to research what this does
    
    mov ax, 0x50

    mov es, ax
    xor bx, bx

    mov al, 2
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0

    mov ah, 0x02
    int 0x13
    jmp 0x50:0x0

    hlt

    times 510-($-$$) db 0
    dw 0xaa55