#include "pathstd.h"
#include "framebuffer.h"

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

    return 0xDEADBEEF;
}
