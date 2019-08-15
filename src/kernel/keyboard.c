#include "io.h"
#include "framebuffer.h"
#include "isr.h"

// lib
#include "../lib/pathstd.h"
#include "../lib/shell.h" // need to be able to tell shell when to flush buffer

void
print_letter(unsigned char scancode)
{
    switch(scancode){
        case 0x2:
            update_shell('1');
            break;
        case 0x3:
            update_shell('2');
            break;
        case 0x4:
            update_shell('3');
            break;
        case 0x5:
            update_shell('4');
            break;
        case 0x6:
            update_shell('5');
            break;
        case 0x7:
            update_shell('6');
            break;
        case 0x8:
            update_shell('7');
            break;
        case 0x9:
            update_shell('8');
            break;
        case 0xa:
            update_shell('9');
            break;
        case 0xb:
            update_shell('0');
            break;
        case 0x10:
            update_shell('Q');
            // fb_write_str(10, 20, "Q", BLACK, WHITE);
            break;
        case 0x11:
            update_shell('W');
            // fb_write_str(10, 20, "W", BLACK, WHITE);
            break;
        case 0x12:
            update_shell('E');
            // fb_write_str(10, 20, "E", BLACK, WHITE);
            break;
        case 0x13:
            update_shell('R');
            break;
        case 0x14:
            update_shell('T');
            break;
        case 0x15:
            update_shell('Y');
            break;
        case 0x16:
            update_shell('U');
            break;
        case 0x17:
            update_shell('I');
            break;
        case 0x18:
            update_shell('O');
            break;
        case 0x19:
            update_shell('P');
            break;
        case 0x1c:
            // enter
            process_cmd();
            break;
        case 0x1e:
            update_shell('A');
            break;
        case 0x1f:
            update_shell('S');
            break;
        case 0x20:
            update_shell('D');
            break;
        case 0x21:
            update_shell('F');
            break;
        case 0x22:
            update_shell('G');
            break;
        case 0x23:
            update_shell('H');
            break;
        case 0x24:
            update_shell('J');
            break;
        case 0x25:
            update_shell('K');
            break;
        case 0x26:
            update_shell('L');
            break;
        case 0x2c:
            update_shell('Z');
            break;
        case 0x2d:
            update_shell('X');
            break;
        case 0x2e:
            update_shell('C');
            break;
        case 0x2f:
            update_shell('V');
            break;
        case 0x30:
            update_shell('B');
            break;
        case 0x31:
            update_shell('N');
            break;
        case 0x32:
            update_shell('M');
            break;
        case 0x39:
            update_shell(' ');
            break;
        default:
            if (scancode <= 0x7f){
                // fb_write_str(10, 20, "Unknown key down", BLACK, WHITE);
            } else if (scancode <= 0x39 + 0x80){
                // fb_write_str(10, 20, "key up", BLACK, WHITE);
            } else {
                // fb_write_str(10, 20, "unknown key up", BLACK, WHITE);
            }
            break;
    }
}

static void
keyboard_callback(regs_t registers)
{
    unsigned char scancode = inb(0x60);
    // fb_write_str(10, 0, "Keyboard input: ", BLACK, WHITE);
    print_letter(scancode);
}

void
init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}