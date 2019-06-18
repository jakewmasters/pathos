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
start: jmp loader

; helper stuff to be called by loader
msg db "Welcome!", 0

cool:
    call clearscreen
    call movecursor
    call writeline

clearscreen:
    ; this block just prints some stuff
    ;lodsb 
    ;or    al, al
    ;jz    done
    ;mov   ah, 0x0e
    ;int   0x10      ; video interrupt
    ;jmp   print

    ; this block clears the window and changes the color
    ; just remember how registers work: bx = 0x[bh][bl]
    mov    ax, 0x0700 ; ah=0x07 means scroll, al=0x00 means whole window
    mov    bh, 0x3F   ; the fun color stuff
    mov    cx, 0x00   ; ch,cl = row,col of top left corner     (0,0)
    mov    dx, 0x184f ; dh,dl = row,col of top right corner  (24,79)
    int    0x10       ; video interrupt
done:
    ret

movecursor:
    mov    ax, 0x0200 ; indicates to set cursor position
    mov    bx, 0x0000 ; clobbering registers bro!
    mov    dx, 0x0000 ; top left
    int    0x10

writeline:
    nop ; multiple ways to do this

; do some cool stuff
; see all of this depends on what you want to do
; for now I'm just going to turn the window into something cool, then...
; 
; clear interrupt flag
; enter halt state
loader:
    ;xor  ax, ax
    ;mov  ds, ax
    ;mov  es, ax
    ;mov  si, msg
    call  cool
    ;xor  ax, ax
    ;int  0x12

    cli
    hlt

; final bootloader touches
; set first 510 bytes to 0
; put magic numbers in last two bytes
; all nasm pseudo-instructions
times 510-($-$$) db 0
dw 0xAA55
