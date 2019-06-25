#include "framebuffer.h"

/*
 * kernel entry point
 */
int
kernel()
{
    int i=0;
    while (i < 80){
        buff_write(i, ' ', BLACK, WHITE);
        ++i;
    }
    buff_write(i+0, 'W', BLACK, CYAN);
    buff_write(i+1, 'e', BLACK, CYAN);
    buff_write(i+2, 'l', BLACK, CYAN);
    buff_write(i+3, 'c', BLACK, CYAN);
    buff_write(i+4, 'o', BLACK, CYAN);
    buff_write(i+5, 'm', BLACK, CYAN);
    buff_write(i+6, 'e', BLACK, CYAN);
    buff_write(i+7, '!', BLACK, CYAN);
    i+=8;
    while (i < 880){
        buff_write(i, ' ', BLACK, WHITE);
        ++i;
    }

    return 0xDEADBEEF;
}