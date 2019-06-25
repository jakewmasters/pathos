#include "io.h"

/*
 * framebuffer writer
 */
void
fb_write(unsigned int i, unsigned char c, unsigned char bg, unsigned char fg)
{
    char *fb = (char *)0x000B8000;
    fb[i*2] = c;
    fb[(i*2)+1] = ((bg & 0x0F) << 4) | (fg & 0x0F); // first byte back, second byte text
}

/*
 * move framebuffer cursor
 */
void
fb_move_cursor(unsigned int row, unsigned int col)
{
    // turn row col into single 2-byte value
    unsigned short pos = (row * 80) + col;

    // send cmds and data to io ports
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_CMD);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_CMD);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

/*
 * overwrite entire framebuffer with DARK_GREY on BLACK
 */
void
fb_clear()
{
    // framebuffer is 25 rows x 80 cols
    for (int i=0; i < 1280; ++i){
        fb_write(i, ' ', 0, 8);
    }
}
