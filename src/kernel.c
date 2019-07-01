#include "pathstd.h"
#include "framebuffer.h"
#include "time.h"

/*
 * kernel entry point
 */
int
kernel()
{
    fb_clear();

    // fb_write(0, 'W', BLACK, CYAN);
    // fb_write(1, 'e', BLACK, CYAN);
    // fb_write(2, 'l', BLACK, CYAN);
    // fb_write(3, 'c', BLACK, CYAN);
    // fb_write(4, 'o', BLACK, CYAN);
    // fb_write(5, 'm', BLACK, CYAN);
    // fb_write(6, 'e', BLACK, CYAN);
    // fb_write(7, '!', BLACK, CYAN);

    char str[64] = "Welcome to PathOS!";
    fb_write_str(10, 30, str, BLACK, CYAN);
    char str2[64] = "A Jake Masters Production.";
    fb_write_str(12, 27, str2, BLACK, CYAN);

    fb_move_cursor(0,0);

    // note: might be having trouble with strings because of either: 
    //  - rodata problems (linker script)
    //  - stack problems... need to set up GDT

    char str3[64] = "Blastoff countdown:";
    fb_write_str(15, 0, str3, BLACK, CYAN);
    sleep(5000000000);
    char str4[64] = "10";
    fb_write_str(16, 0, str4, BLACK, CYAN);
    sleep(1000000000);
    char str5[64] = "9 ";
    fb_write_str(16, 0, str5, BLACK, CYAN);
    sleep(1000000000);
    char str6[64] = "8 ";
    fb_write_str(16, 0, str6, BLACK, CYAN);
    sleep(1000000000);
    char str7[64] = "7 ";
    fb_write_str(16, 0, str7, BLACK, CYAN);
    sleep(1000000000);
    char str8[64] = "6 ";
    fb_write_str(16, 0, str8, BLACK, CYAN);
    sleep(1000000000);
    char str9[64] = "5 ";
    fb_write_str(16, 0, str9, BLACK, CYAN);
    sleep(1000000000);
    char str10[64] = "4 ";
    fb_write_str(16, 0, str10, BLACK, CYAN);
    sleep(1000000000);
    char str11[64] = "3 ";
    fb_write_str(16, 0, str11, BLACK, CYAN);
    sleep(1000000000);
    char str12[64] = "2 ";
    fb_write_str(16, 0, str12, BLACK, CYAN);
    sleep(1000000000);
    char str13[64] = "1 ";
    fb_write_str(16, 0, str13, BLACK, CYAN);
    sleep(1000000000);
    char str14[64] = "BLASTOFF!";
    fb_write_str(16, 0, str14, BLACK, CYAN);

    /* TODO:
     * write timer device driver
     * write keyboard driver
     * add shell
     */

    return 0xDEADBEEF;
}
