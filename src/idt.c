/*
 * Interrupt Descriptor Table (IDT)
 *
 * The IDT has 256 8-byte entries. 
 * Each entry is set up in a special way. 
 */

#include "framebuffer.h"
#include "idt.h"

/*
 * set IDT entry
 */
void
set_idt_entry(int i, unsigned int handler)
{
    idt[i].offset_low = handler & 0xFFFF; // just want lower 16 bits
    idt[i].selector = 0x8; // offset into GDT
    idt[i].zero = 0;
    idt[i].type = 0x8E;
    idt[i].offset_high = (handler >> 16) & 0xFFFF;
}

/*
 * public function, called by kmain
 * populates idt entries and calls lidt
 */
void
idt_init()
{
    // fb_write_str(5,0,"Initializing IDT...", BLACK, WHITE);

    // idt defined in header
    idt_desc.base = (unsigned int) &idt;
    idt_desc.limit = IDT_ENTRIES * sizeof(idt_entry_t)-1;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_desc));
}