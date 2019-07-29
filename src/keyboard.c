#include "io.h"
#include "framebuffer.h"
#include "pathstd.h"
#include "isr.h"

// need to be able to tell shell when to flush buffer
#include "shell.h"

void
print_letter(unsigned char scancode)
{
    switch(scancode){
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
            fb_write_str(10, 20, "R", BLACK, WHITE);
            break;
        case 0x14:
            fb_write_str(10, 20, "T", BLACK, WHITE);
            break;
        case 0x15:
            fb_write_str(10, 20, "Y", BLACK, WHITE);
            break;
        default:
            if (scancode <= 0x7f){
                // fb_write_str(10, 20, "Unknown key down", BLACK, WHITE);
            } else if (scancode <= 0x39 + 0x80){
                fb_write_str(10, 20, "key up", BLACK, WHITE);
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
    fb_write_str(10, 0, "Keyboard input: ", BLACK, WHITE);
    print_letter(scancode);
}

void
init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}