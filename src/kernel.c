#include "framebuffer.h"
#include "time.h"
#include "isr.h"
#include "keyboard.h"
#include "shell.h"

#if defined(__linux__)
#error "need to use cross-compiler"
#endif

#if !defined(__i386__)
#error "compile for the right target ;)"
#endif

void
welcome()
{
   fb_write_str(0,30, "Welcome to", BLACK, GREEN);

   // row 2: 160
   // row 3: 240
   // row 4: 320

   fb_write(180,219, BLACK, MAGENTA);
   fb_write(181,219, BLACK, MAGENTA);
   fb_write(182,219, BLACK, MAGENTA);
   fb_write(183,219, BLACK, MAGENTA);
   fb_write(184,219, BLACK, MAGENTA);
   fb_write(260,219, BLACK, MAGENTA);
   fb_write(340,219, BLACK, MAGENTA);
   fb_write(420,219, BLACK, MAGENTA);
   fb_write(264,219, BLACK, MAGENTA);
   fb_write(341,219, BLACK, MAGENTA);
   fb_write(342,219, BLACK, MAGENTA);
   fb_write(343,219, BLACK, MAGENTA);
   fb_write(344,219, BLACK, MAGENTA);
   fb_write(500,219, BLACK, MAGENTA); // P

   fb_write(346,219, BLACK, MAGENTA);
   fb_write(347,219, BLACK, MAGENTA);
   fb_write(348,219, BLACK, MAGENTA);
   fb_write(426,219, BLACK, MAGENTA);
   fb_write(428,219, BLACK, MAGENTA);
   fb_write(506,219, BLACK, MAGENTA);
   fb_write(507,219, BLACK, MAGENTA);
   fb_write(508,219, BLACK, MAGENTA);
   fb_write(586,219, BLACK, MAGENTA);
   fb_write(588,219, BLACK, MAGENTA); // A

   fb_write(190,219, BLACK, MAGENTA);
   fb_write(191,219, BLACK, MAGENTA);
   fb_write(192,219, BLACK, MAGENTA);
   fb_write(271,219, BLACK, MAGENTA);
   fb_write(351,219, BLACK, MAGENTA);
   fb_write(431,219, BLACK, MAGENTA); // T

   fb_write(354,219, BLACK, MAGENTA);
   fb_write(356,219, BLACK, MAGENTA);
   fb_write(434,219, BLACK, MAGENTA);
   fb_write(435,219, BLACK, MAGENTA);
   fb_write(436,219, BLACK, MAGENTA);
   fb_write(514,219, BLACK, MAGENTA);
   fb_write(516,219, BLACK, MAGENTA);
   fb_write(594,219, BLACK, MAGENTA);
   fb_write(596,219, BLACK, MAGENTA); // H

   fb_write(198,219, BLACK, MAGENTA);
   fb_write(199,219, BLACK, MAGENTA);
   fb_write(200,219, BLACK, MAGENTA);
   fb_write(278,219, BLACK, MAGENTA);
   fb_write(280,219, BLACK, MAGENTA);
   fb_write(358,219, BLACK, MAGENTA);
   fb_write(360,219, BLACK, MAGENTA);
   fb_write(438,219, BLACK, MAGENTA);
   fb_write(439,219, BLACK, MAGENTA);
   fb_write(440,219, BLACK, MAGENTA); // O

   fb_write(282,219, BLACK, MAGENTA);
   fb_write(283,219, BLACK, MAGENTA);
   fb_write(284,219, BLACK, MAGENTA);
   fb_write(362,219, BLACK, MAGENTA);
   fb_write(442,219, BLACK, MAGENTA);
   fb_write(443,219, BLACK, MAGENTA);
   fb_write(444,219, BLACK, MAGENTA);
   fb_write(524,219, BLACK, MAGENTA);
   fb_write(602,219, BLACK, MAGENTA);
   fb_write(603,219, BLACK, MAGENTA);
   fb_write(604,219, BLACK, MAGENTA);


   return;
}

int kmain(){
   fb_clear();
   welcome();
   // fb_disable_cursor();

   // char *str = "Welcome!";
   // fb_write_str(10, 30, str, BLACK, CYAN);

   // fb_move_cursor(0,0);

   /*
   * Next steps:
   * - IDT + interrupt stuff
   * - Keyboard
   * - Audio y e e t
   */
   isrs_init();

   // test interrupt
   // __asm__ __volatile__("int $20");

   // fb_write_str(3,0,"Wow we made it!", BLACK, LIGHT_BLUE);

   /* alright everything below except init_keyboard() is new */

   init_keyboard();

   /* 7/28: just a heads-up, git isn't working for some reason. 
      i re-inited and added remote origin, just can't auth
      all i'm doing is adding a fake shell, linking in shell.h
   */

   fake_shell();
   // fb_write_str(20,0, "made it here", BLACK, WHITE);

   /*
      Operation Ragnaros: BY FIRE BE PURGED!
         - Time to clean everything up. 
         - The goal is to have a simple, text-mode OS. 
         - Currently, the shell governs all input. 
         - Let's create a buffer manager so we can first pop up a menu, and from there either use a shell or (hopefully) a video GUI. 
     */

   // what should the kernel do?
   // 1. welcome display
   // 2. load stuff in background
   // 3. start user interaction

   return 0xdeadbeef;
}