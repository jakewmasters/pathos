; PathOS bootloader
; by Jake Masters

[org 0x7c00]
start:
    mov [BOOT_DRIVE], dl

    ; setup segment registers
    xor ax, ax
    mov ds, ax
    mov ss, ax

    ; setup stack
    mov bp, 0x8000 ; 1 kb past start of code
    mov sp, bp

    ; load 5 sectors from boot disk
    mov bx, 0x9000
    mov dh, 5
    mov dl, [BOOT_DRIVE]
    call disk_load

    ; check to see if sectors loaded correctly
    mov dx, [0x9000]
    call print_hex


hang:
    jmp hang


; extra functions
disk_load:
    push dx
    mov ah, 0x02
    mov al, dh
    mov ch, 0x0
    mov dh, 0x0
    mov cl, 0x02
    int 0x13
    jc disk_error
    pop dx
    cmp dh, al
    jne disk_error
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp hang

print_string:
    pusha
    mov ah, 0x0e
loop:
    mov al, [bx]
    int 0x10
    add bx, 1
    cmp al, 0
    jne loop
    popa
    ret

print_hex:
    mov cx, dx
    and cx, 0xf000
    shr cx, 12
    call to_char
    mov [HEX_OUT + 2], cx

    mov cx, dx
    and cx, 0x0f00
    shr cx, 8
    call to_char
    mov [HEX_OUT + 3], cx

    mov cx, dx
    and cx, 0x00f0
    shr cx, 4
    call to_char
    mov [HEX_OUT + 4], cx

    mov cx, dx
    and cx, 0x000f
    call to_char
    mov [HEX_OUT + 5], cx

    mov bx, HEX_OUT
    call print_string
    mov byte [HEX_OUT + 2], '0'
    mov byte [HEX_OUT + 3], '0'
    mov byte [HEX_OUT + 4], '0'
    mov byte [HEX_OUT + 5], '0'
    ret

to_char:
    cmp cx, 0xa
    jl digits
    sub cx, 0xa
    add cx, 'a'
    ret
digits:
    add cx, '0'
    ret

; bootloader variables
BOOT_DRIVE: db 0
DISK_ERROR_MSG db "Disk read error!", 0
HEX_OUT: db '0x0000', 0

; sign boot sector
times 510-($-$$) db 0
dw 0xaa55

; fill up some other sectors
times 256 dw 0xdada
times 256 dw 0xdada
