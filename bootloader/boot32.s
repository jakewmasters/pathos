; PathOS bootloader
; by Jake Masters

; this bootloader switches from 16-bit real mode
; to 32-bit protected mode

; the following two lines cause the entire OS to be position-dependent
[org 0x7c00]
KERNEL_OFFSET equ 0x1000

; bootloader entry point
start:
    ; setup stack
    mov bp, 0x9000
    mov sp, bp

    ; start output
    call bios_clearscreen
    mov dx, 0x0000
    call bios_move_cursor
    mov bx, REAL_MSG
    call bios_print

    call load_kernel

    ; the BIG switch
    call switch_to_pm
    
    jmp hang ; should never reach this

hang:
    jmp hang

;; helper functions for 16-bit real mode ONLY ;;

bios_print:
    pusha
    mov ah, 0x0e
bios_loop:
    mov al, [bx] ; bx will have string to print
    int 0x10
    add bx, 1
    cmp al, 0    ; stops when null byte found
    jne bios_loop
    popa
    ret

bios_clearscreen:
    pusha
    mov ax, 0x0700  ; scroll mode
    mov bh, 0x0b    ; 0x[back][text]
    mov cx, 0x0000  ; top left corner
    mov dx, 0x184f  ; bottom right corner
    int 0x10
    popa
    ret

; dh = row, dl = col
bios_move_cursor:
    pusha
    mov ah, 0x02  ; cursor mode
    mov bh, 0x00  ; page number
    int 0x10
    popa
    ret

;; end real mode helper functions ;;

;; functions for loading kernel into memory ;;

[bits 16]

load_kernel:
    mov dx, 0x0100
    call bios_move_cursor
    mov bx, LOAD_MSG
    call bios_print

    ; load first 15 sectors off of disk
    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

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
    mov dx, 0x0200
    call bios_move_cursor
    mov bx, DISK_ERROR_MSG
    call bios_print
    jmp hang

switch_to_pm:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:init_pm

;; end kernel load functions ;;


; THE GREAT DIVIDE (between real mode and protected mode)
; /\/\/\/\/\/\/\/\


;; once kernel and GDT are loaded, call kernel ;;

[bits 32]
BEGIN_PM:
    mov ebx, PROT_MSG
    mov ax, 480
    call print_string

    mov ebx, LOAD_MSG
    mov ax, 640
    call print_string

    ; call kernel
    call KERNEL_OFFSET  ; here we go!

    jmp hang

;; 32-bit helper functions ;;

init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp
    call BEGIN_PM

;; helper functions for 32-bit protected mode ;;

print_string:
    pusha
    add eax, VRAM
    mov edx, eax  ; move cursor by value stored in ax (1 row = 80 cols * 2 bytes per entry)
loop:
    mov al, [ebx]
    mov ah, COLOR
    cmp al, 0
    je done
    mov [edx], ax
    add ebx, 1
    add edx, 2
    jmp loop
done:
    popa
    ret

;; end helper functions for 32-bit protected mode ;;

;; GDT specification ;;

gdt_start:

gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

;; end GDT specification ;;

; bootloader static variables
VRAM equ 0xb8000
COLOR equ 0x0b
BOOT_DRIVE: db 0
DISK_ERROR_MSG db "Could not read disk...", 0
LOAD_MSG db "Loading kernel into memory...", 0
REAL_MSG db "Starting in 16-bit real mode...", 0
PROT_MSG db "Switched to 32-bit protected mode!", 0

; sign boot sector
times 510-($-$$) db 0
dw 0xaa55
