; operating in 16 bit real mode
bits 16

; setup a little stack to use in our bootloader
mov ax, 0x07C0
mov ds, ax
mov ax, 0x07E0
mov ss, ax
mov sp, 0x2000

call clearscreen

push 0x0000
call movecursor
add sp, 2

push msg
call print
add sp, 2

cli
hlt

; some fun BIOS things to know
; - int 0x10 sends a video interrupt. when this happens: 
;   - if ah has 0x07, the window will scroll. 
;   - the value in al indicates how far to scroll. 0x00 clears the whole window. 
;   - bl indicates background color
;   - bh indicates text color
; reference for interrupts: http://www.ctyme.com/intr/int.htm
clearscreen:
    push bp           ; adhering to classic stack stuff
    mov bp, sp
    pusha             ; save caller

    ; mov ah, 0x07    ; scroll
    ; mov al, 0x00    ; how far to scroll (0x00 clears screen)
    mov ax, 0x0700    ; combines both into one step
    mov bh, 0x3F      ; 0x[back][text] see https://en.wikipedia.org/wiki/BIOS_color_attributes
    mov cx, 0x00      ; clear from top left corner of screen
    mov dh, 0x18      ; how many rows
    mov dl, 0x4f      ; how many cols
    int 0x10          ; video interrupt!

    popa              ; more adherance to stack stuff
    mov sp, bp        ; restore caller stuff
    pop bp
    ret

movecursor:
    push bp
    mov bp, sp
    pusha

    mov dx, [bp+4]
    mov ah, 0x02
    mov bh, 0x00
    int 0x10

    popa
    mov sp, bp
    pop bp
    ret

print:
    push bp
    mov bp, sp
    pusha
    mov si, [bp+4]
    mov bh, 0x00
    mov bl, 0x00
    mov ah, 0x0E
.char:
    mov al, [si]
    add si, 1
    or al, 0
    je .return
    int 0x10
    jmp .char
.return:
    popa
    mov sp, bp
    pop bp
    ret

msg:    db "is anybody out here?", 0

times 510-($-$$) db 0
dw 0xAA55
