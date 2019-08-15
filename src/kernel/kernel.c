#include "framebuffer.h"
#include "time.h"
#include "isr.h"
#include "keyboard.h"
#include "vm.h"

// lib
#include "../lib/shell.h"


#if defined(__linux__)
#error "need to use cross-compiler"
#endif

#if !defined(__i386__)
#error "compile for the right target ;)"
#endif


/*
 * Main Goals:
 *   - enable paging
 *   - filesystem
 *   - finish shell
 *   - add basic, text-based applications (text editor)
 * On the Horizon:
 *   - video mode GUI
 *   - audio support
 *   - user processes
 */

int kmain(){
   fb_clear();
   // fb_disable_cursor();
   // char *str = "Welcome!";
   // fb_write_str(10, 30, str, BLACK, CYAN);
   // fb_move_cursor(0,0);

   isrs_init();

   init_keyboard();

   // fake_shell();

   // enable_paging();

   /*
      Operation Ragnaros: BY FIRE BE PURGED!
         - Time to clean everything up. 
         - The goal is to have a simple, text-mode OS. 
         - Currently, the shell governs all input. 
         - Let's create a buffer manager so we can first pop up a menu, and from there either use a shell or (hopefully) a video GUI. 
     */

   char *test = "this is just a test string";

   return 0xdeadbeef;
}