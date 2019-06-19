; PathOS bootloader
; by Jake Masters

bits 16
org  0x7c00

start:
    jmp    loader


; dl holds what we're searching for
; cl holds what we found
; bx holds address

search:
    mov    dl, 0x34
    mov    bx, 0x8110
    mov    ds, bx
    mov    bx, 0
.loop inc  bx
    mov BYTE   cl, [bx+0] ; this is not doing what I want to...
    cmp    dl, cl
    ;je     found
    cmp    bx, 0x8C24
    ;jge    lost
    jmp    .loop
    ret

; turn screen green
found:
    mov    ax, 0x0700
    mov    bh, 0x2F
    mov    cx, 0x00
    mov    dx, 0x184f
    int    0x10
    ret

; turn screen red
lost:
    mov    ax, 0x0700
    mov    bh, 0x4F
    mov    cx, 0x00
    mov    dx, 0x184f
    int    0x10
    ret

other:
    nop
    ret


loader:
    call search
    call sign

sign:
    times 510-($-$$) db 0
    dw 0xaa55

extend:
    times 758-($-$$) db 1
    db    0x34
    times 1024-($-$$) db 1