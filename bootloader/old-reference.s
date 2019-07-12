; just for reference, has some code from OSDev that does stuff
; by Jake Masters

[org 0x7c00]
start:
    xor ax, ax
    mov ds, ax ; put data segment at 0, since whole program is offset at 0x7c00
    mov ss, ax ; same thing for stack segment
    mov sp, 0x9c00 ; put actual stack 8K past code start
    
    cld

    mov ax, 0xb800
    mov es, ax ; setting extra segment as start of video memory

    mov si, msg ; load string into register
    mov dx, 0 ; using dx to hold video memory index



    mov si, msg
    call print_str

hang:
    jmp hang

msg db 'Hello world', 0

print_str:
    lodsb
    or al, al
    jz done
    ;mov cx, [es:dx] ; compute vga address
    ;mov cx, al ; send char to vga
    add dx, $1
    jmp print_str
done:
    ret

times 510-($-$$) db 0
dw 0xaa55
