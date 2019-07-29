#include "framebuffer.h"
#include "time.h"
#include "isr.h"
#include "keyboard.h"
/* new, make sure this doesn't get screwed by git */
#include "shell.h"

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

    /* alright everything below except init_keyboard() is new */

    init_keyboard();

    /* 7/28: just a heads-up, git isn't working for some reason. 
       i re-inited and added remote origin, just can't auth
       all i'm doing is adding a fake shell, linking in shell.h
    */

    fake_shell();

    return 0xdeadbeef;
}