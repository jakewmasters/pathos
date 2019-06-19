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
msg db "Loading PathOS v0.1...", 0

; OEM data
; db, dw, and dd are all NASM pseudo-instructions
bpbOEM                db "PathOS  "
bpbBytesPerSector:    dw 512
bpbSectorsPerCluster: db 1
bpbReservedSectors:   dw 1
bpbNumberOfFATs:      db 2
bpbRootEntries:       db 224
bpbTotalSectors:      dw 2880
bpbMedia:             db 0xF0
bpbSectorsPerFAT:     dw 9
bpbSectorsPerTrack:   dw 18
bpbHeadsPerCylinder:  dw 2
bpbHiddenSectors:     dd 0
bpbTotalSectorsBig:   dd 0
bsDriveNumber:        db 0
bsUnused:             db 0
bsExtBootSignature:   db 0x29
bsSerialNumber:       dd 0xa0a1a2a3
bsVolumeLabel:        db "MOS FLOPPY "
bsFileSystem:         db "FAT16   "
; end OEM data


; this gets called before final bootloader stuff
; run all the cool stuff while you can!
stuff:
    call clearscreen
    call movecursor
    call writeline
    ret

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

; find next part
search:
    ret

; do some cool stuff
; see all of this depends on what you want to do
; for now I'm just going to turn the window into something cool, then...
; clear interrupt flag
; enter halt state
loader:
    call  stuff
    call  sign
    call  extend
    call  search
    jmp   end

; final bootloader touches
; set first 510 bytes to 0
; put magic numbers in last two bytes
; all nasm pseudo-instructions
sign:
    times 510-($-$$) db 0
    dw 0xAA55
    ret

; create another sector so that we can find
extend:
    dw 0x34
    times 1023-($-$$) db 0 ; double our bootloader size
    ret

end:
    cli
    hlt

; notes
; so the tutorial is using FAT12, but I think I might try emulating FAT16 since I know how it works
