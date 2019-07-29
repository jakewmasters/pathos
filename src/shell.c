#include "framebuffer.h"

// global shell data
unsigned int fb_row; // there are 25 of these
unsigned int fb_col; // there are 80 of these
unsigned int buf_index; // there are 80 of these

void
fake_shell()
{
    // local data
    fb_row = 0; // start shell at beginning
    fb_col = 0;

    // for sake of simplicity, let's have this thing call the shots on the keyboard buffer

    fb_clear();
    fb_write_str(fb_row, fb_col,"shell> ", BLACK, WHITE);
}

/*
    Strategy: don't even store characters, just print them directly. Just to start :)
 */
void
update_shell(unsigned char letter)
{
    if (fb_col == 0){
        fb_col = 7;
    } else {
        fb_col++;
    }
    fb_write((fb_row*80)+fb_col, letter, BLACK, WHITE);
}

/*
    End of day: 7/28

    everything is working as expected
    when Q, W, or E is pressed, the correct character is put in the right spot on the shell. 
 */