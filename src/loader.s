; bridge between GRUB and kernel

global loader

extern kernel

; headers
MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER
KERNEL_STACK_SIZE equ 16384 ; 16K stack

section .bss
align 16
stack_bottom:
    resb KERNEL_STACK_SIZE
stack_top:

section .text:
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    mov edx, 0xCAFEBABE

higher_half:
    mov esp, stack_top
    mov edx, 0x00c0ffee

enter_kernel:
    call kernel

hang:
    jmp hang
