#include "framebuffer.h"
#include "time.h"
#include "isr.h"
#include "keyboard.h"

#if defined(__linux__)
#error "need to use cross-compiler"
#endif

#if !defined(__i386__)
#error "compile for the right target ;)"
#endif

int kmain(){
    fb_clear();

    // char *str = "Welcome!";
    // fb_write_str(10, 30, str, BLACK, CYAN);

    // fb_move_cursor(0,0);

    /*
     * Next steps:
     * - IDT + interrupt stuff
     * - Keyboard
     * - Audio y e e t
     */
    isrs_init();

    // test interrupt
    // __asm__ __volatile__("int $20");

    // fb_write_str(3,0,"Wow we made it!", BLACK, LIGHT_BLUE);

    init_keyboard();

    return 0xdeadbeef;
}