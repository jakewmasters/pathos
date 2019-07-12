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
    mov bp, 0x8c00 ; 4 kb past start of code
    mov sp, bp

    ; load 5 sectors from boot disk
    mov bx, 0x9000        ; bx = buffer
    mov dh, 5             ; 5 sectors
    mov dl, [BOOT_DRIVE]  ; drive set to BOOT_DRIVE
    call disk_load

    ; check to see if sectors loaded correctly
    mov dx, [0x9000] ; 2 bytes of hex data stored in dx
    call print_hex

    ; test second print_hex
    mov dx, 0x1234
    call print_hex

hang:
    jmp hang


;; extra functions ;;

disk_load:
    push dx
    mov ah, 0x02  ; set disk read mode in BIOS
    mov al, dh    ; number of sectors to read
    mov ch, 0x0   ; cylinder number
    mov dh, 0x0   ; head
    mov cl, 0x02  ; sector
    int 0x13      ; call interrupt to read!
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
    mov al, [bx] ; bx will have string to print
    int 0x10
    add bx, 1
    cmp al, 0    ; stops when null byte found
    jne loop
    popa
    ret

; WARNING: does not clear hex string, must set dx every time
print_hex:
    mov cx, dx
    and cx, 0xf000         ; grab most significant byte
    shr cx, 12             ; shift to cl
    call to_char
    mov [HEX_OUT + 2], cx  ; place char in hex string after 0x prefix

    mov cx, dx
    and cx, 0x0f00         ; repeat for second most significant byte
    shr cx, 8
    call to_char
    mov [HEX_OUT + 3], cx

    mov cx, dx
    and cx, 0x00f0         ; repeat for third most significant byte
    shr cx, 4
    call to_char
    mov [HEX_OUT + 4], cx

    mov cx, dx
    and cx, 0x000f         ; repeat for least significant byte
    call to_char
    mov [HEX_OUT + 5], cx

    mov bx, HEX_OUT
    call print_string
    ret

; stores appropriate char in cx
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
DISK_ERROR_MSG db "Could not read disk...", 0
HEX_OUT: db '0x0000', 0

; sign boot sector
times 510-($-$$) db 0
dw 0xaa55

; fill up some other sectors
times 256 dw 0xdada
times 256 dw 0xdada
