#include "framebuffer.h"
#include "pathstd.h"

// global shell data
unsigned int fb_row = -1; // there are 25 of these
unsigned int fb_col = 0; // there are 80 of these

char *cmd_buf = "                                                              "; // now THIS is arbitrary
unsigned int buf_index = 0; // there are 80 of these

void
fake_shell()
{
    // local data
    fb_row++; // start shell at beginning
    fb_col = 0;

    // for sake of simplicity, let's have this thing call the shots on the keyboard buffer

    // fb_clear();
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
    fb_move_cursor(fb_row, fb_col+1);
    cmd_buf[buf_index] = letter;
    buf_index++; // better hope buffer is not exceeded!
}

void
process_cmd()
{
    fb_row++;
    fb_col = 7;
    fb_write_str(fb_row, fb_col, "Processing command: ", BLACK, WHITE);

    // verify command entered
    cmd_buf[buf_index] = '\0';
    fb_write_str(fb_row, fb_col+20, cmd_buf, BLACK, WHITE);

    // strcmp, do stuff based on input
    if (strcmp(cmd_buf, "HELP") == 0){
        fb_row++;
        fb_write_str(fb_row, fb_col, "You have entered the HELP command.", BLACK, WHITE);
    } else
    if (strcmp(cmd_buf, "EXIT") == 0){
        fb_row++;
        fb_write_str(fb_row, fb_col, "Exiting...", BLACK, RED);
        return;
    } else 
    if (strcmp(cmd_buf, "BEEP") == 0){
        fb_row++;
        fb_write_str(fb_row, fb_col, "beeping...", BLACK, MAGENTA);
    }

    // take user input again
    buf_index = 0;
    cmd_buf = "                                                              ";
    fake_shell();
}
