; bridge between GRUB and kernel

global loader

extern kmain

; headers
MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER
KERNEL_STACK_SIZE equ 4096

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text:
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    mov edx, 0xCAFEBABE
;.loop:
;    jmp .loop

higher_half:
    mov esp, kernel_stack + KERNEL_STACK_SIZE

enter_kmain:
    call kmain

hang:
    jmp hang