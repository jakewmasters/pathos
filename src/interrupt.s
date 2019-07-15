[extern isr_handler]

isr_common:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call isr_handler
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    sti
    iret

global isr0
global isr1
global isr2

isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common

isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common

isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common
