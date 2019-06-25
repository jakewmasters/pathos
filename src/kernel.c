#include "framebuffer.h"

/*
 * kernel entry point
 */
int
kernel()
{
    fb_clear();

    fb_write(0, 'W', BLACK, CYAN);
    fb_write(1, 'e', BLACK, CYAN);
    fb_write(2, 'l', BLACK, CYAN);
    fb_write(3, 'c', BLACK, CYAN);
    fb_write(4, 'o', BLACK, CYAN);
    fb_write(5, 'm', BLACK, CYAN);
    fb_write(6, 'e', BLACK, CYAN);
    fb_write(7, '!', BLACK, CYAN);

    fb_move_cursor(0, 8);

    return 0xDEADBEEF;
}
