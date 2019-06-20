;=============================
; PathOS bootloader - stage 0
; by Jake Masters
;=============================

bits 16

org 0

start:
    jmp main

load:
    nop
    ret

main:
    cli
    ; adjust segment registers
    mov    ax, 0x07c0
    mov    ds, ax        ; data segment
    mov    es, ax        ; extra segment
    mov    fs, ax        ; general-purpose
    mov    gs, ax        ; general-purpose
    ; create stack
    mov    ax, 0x0000
    mov    ss, ax
    mov    sp, 0xFFFF
    sti

    ; do all of our loading here
    call load
    ; treat load as a black box, it should just work

    times 510-($-$$) db 0
    dw 0xaa55