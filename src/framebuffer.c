/*
 * framebuffer writer
 */
void
buff_write(unsigned int i, unsigned char c, unsigned char bg, unsigned char fg)
{
    char *fb = (char *)0x000B8000;
    fb[i*2] = c;
    fb[(i*2)+1] = ((bg & 0x0F) << 4) | (fg & 0x0F); // first byte back, second byte text
}

void
move_cursor(unsigned int row, unsigned int col)
{
    unsigned int rowcol = row + col;
    rowcol++;
    return;
}