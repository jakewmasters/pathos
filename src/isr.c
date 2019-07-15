#include "isr.h"
#include "idt.h"
#include "framebuffer.h"

char *exception_messages[] = {
    "Division by zero",
    "Debug",
    "Non Maskable Interrupt"
};

void
isrs_init()
{
    fb_write_str(4,0,"registering isrs...", BLACK, WHITE);
    idt_init();
    set_idt_entry(0, (unsigned int)isr0);
    set_idt_entry(1, (unsigned int)isr1);
    set_idt_entry(2, (unsigned int)isr2);
}

// will have additional functionality, eventually
void
isr_handler()
{
    fb_write_str(5,0,"received interrupt", BLACK, WHITE);
}