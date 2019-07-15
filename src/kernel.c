#include "framebuffer.h"
#include "time.h"
#include "isr.h"

#if defined(__linux__) // cheating here, need to actually use cross-compiler
#error "need to use cross-compiler"
#endif

#if !defined(__i386__)
#error "compile for the right target ;)"
#endif

int kmain(){
    // fb_clear();

    // char *str = "Welcome!";
    // fb_write_str(10, 30, str, BLACK, CYAN);

    // fb_move_cursor(0,0);

    // char str3[64] = "Blastoff countdown:";
    // fb_write_str(15, 0, str3, BLACK, CYAN);
    // sleep(5);
    // char str4[64] = "10";
    // fb_write_str(16, 0, str4, BLACK, CYAN);
    // sleep(1);
    // char str5[64] = "9 ";
    // fb_write_str(16, 0, str5, BLACK, CYAN);
    // sleep(1);
    // char str6[64] = "8 ";
    // fb_write_str(16, 0, str6, BLACK, CYAN);
    // sleep(1);
    // char str7[64] = "7 ";
    // fb_write_str(16, 0, str7, BLACK, CYAN);
    // sleep(1);
    // char str8[64] = "6 ";
    // fb_write_str(16, 0, str8, BLACK, CYAN);
    // sleep(1);
    // char str9[64] = "5 ";
    // fb_write_str(16, 0, str9, BLACK, CYAN);
    // sleep(1);
    // char str10[64] = "4 ";
    // fb_write_str(16, 0, str10, BLACK, CYAN);
    // sleep(1);
    // char str11[64] = "3 ";
    // fb_write_str(16, 0, str11, BLACK, CYAN);
    // sleep(1);
    // char str12[64] = "2 ";
    // fb_write_str(16, 0, str12, BLACK, CYAN);
    // sleep(1);
    // char str13[64] = "1 ";
    // fb_write_str(16, 0, str13, BLACK, CYAN);
    // sleep(1);
    // char str14[64] = "BLASTOFF!";
    // fb_write_str(16, 0, str14, BLACK, CYAN);

    /*
     * Next steps:
     * - IDT + interrupt stuff
     * - Keyboard
     * - Audio y e e t
     */
    fb_clear();
    isrs_init();

    __asm__ __volatile__("int $0");

    fb_write_str(3,0,"Wow we made it!", BLACK, LIGHT_BLUE);

    return 0xdeadbeef;
}