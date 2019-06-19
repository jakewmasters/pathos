;=====================
; pathos bootloader
; by jake masters
;=====================

; run in 16-bit real mode
; load at 0x7c00
; both nasm specific
bits 16
org 0x7c00 ; i think this is a segment:offset address

; starting point
start: 
    jmp loader

; variables
msg db "PathOS v0.1!", 0

; this gets called before final bootloader stuff
; run all the cool stuff while you can!
stuff:
    call clearscreen
    call movecursor
    call writeline
    call oemwriter ; just testing some stuff
    jmp end

; here are all the helper functions
clearscreen:
    ; this block clears the window and changes the color
    ; just remember how registers work: bx = 0x[bh][bl]
    mov    ax, 0x0700 ; ah=0x07 means scroll, al=0x00 means whole window
    mov    bh, 0x3F   ; the fun color stuff
    mov    cx, 0x00   ; ch,cl = row,col of top left corner     (0,0)
    mov    dx, 0x184f ; dh,dl = row,col of top right corner  (24,79)
    int    0x10       ; video interrupt
    ret

movecursor:
    mov    ax, 0x0200 ; indicates to set cursor position
    mov    bx, 0x0000 ; clobbering registers bro!
    mov    dx, 0x0000 ; top left
    int    0x10
    ret

writeline:
    mov    si, msg
    mov    ah, 0x0E
.loop lodsb
    or     al, al
    jz     .end
    int 0x10
    jmp .loop
.end ret
    

oemwriter:
    mov    ax, 0x0200 ; set-cursor mode
    mov    bx, 0x0000 ; move cursor stuff
    mov    dx, 0x0100 ; next row
    int    0x10
    nxt db "next line!", 0
    mov    si, nxt
    mov    ah, 0x0E
.loop lodsb
    or     al, al
    jz     end
    int 0x10
    jmp .loop

; do some cool stuff
; see all of this depends on what you want to do
; for now I'm just going to turn the window into something cool, then...
; clear interrupt flag
; enter halt state
loader:
    call  stuff

end:
    cli
    hlt

; final bootloader touches
; set first 510 bytes to 0
; put magic numbers in last two bytes
; all nasm pseudo-instructions
times 510-($-$$) db 0
dw 0xAA55
