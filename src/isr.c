#include "isr.h"
#include "idt.h"
#include "framebuffer.h"
#include "pathstd.h"
#include "io.h"

// will this be ok?
isr_t interrupt_handlers[256];

/*
 * Initialize IDT
 * and register each ISR
 */
void
isrs_init()
{
    set_idt_entry(0, (unsigned int)isr0);
    set_idt_entry(1, (unsigned int)isr1);
    set_idt_entry(2, (unsigned int)isr2);
    set_idt_entry(3, (unsigned int)isr3);
    set_idt_entry(4, (unsigned int)isr4);
    set_idt_entry(5, (unsigned int)isr5);
    set_idt_entry(6, (unsigned int)isr6);
    set_idt_entry(7, (unsigned int)isr7);
    set_idt_entry(8, (unsigned int)isr8);
    set_idt_entry(9, (unsigned int)isr9);
    set_idt_entry(10, (unsigned int)isr10);
    set_idt_entry(11, (unsigned int)isr11);
    set_idt_entry(12, (unsigned int)isr12);
    set_idt_entry(13, (unsigned int)isr13);
    set_idt_entry(14, (unsigned int)isr14);
    set_idt_entry(15, (unsigned int)isr15);
    set_idt_entry(16, (unsigned int)isr16);
    set_idt_entry(17, (unsigned int)isr17);
    set_idt_entry(18, (unsigned int)isr18);
    set_idt_entry(19, (unsigned int)isr19);
    set_idt_entry(20, (unsigned int)isr20);
    set_idt_entry(21, (unsigned int)isr21);
    set_idt_entry(22, (unsigned int)isr22);
    set_idt_entry(23, (unsigned int)isr23);
    set_idt_entry(24, (unsigned int)isr24);
    set_idt_entry(25, (unsigned int)isr25);
    set_idt_entry(26, (unsigned int)isr26);
    set_idt_entry(27, (unsigned int)isr27);
    set_idt_entry(28, (unsigned int)isr28);
    set_idt_entry(29, (unsigned int)isr29);
    set_idt_entry(30, (unsigned int)isr30);
    set_idt_entry(31, (unsigned int)isr31);

    // remap PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xa1, 0x28);
    outb(0x21, 0x04);
    outb(0xa1, 0x02);
    outb(0x21, 0x01);
    outb(0xa1, 0x01);
    outb(0x21, 0x0);
    outb(0xa1, 0x0);

    // install irqs
    set_idt_entry(32, (unsigned int)irq0);
    set_idt_entry(33, (unsigned int)irq1);
    set_idt_entry(34, (unsigned int)irq2);
    set_idt_entry(35, (unsigned int)irq3);
    set_idt_entry(36, (unsigned int)irq4);
    set_idt_entry(37, (unsigned int)irq5);
    set_idt_entry(38, (unsigned int)irq6);
    set_idt_entry(39, (unsigned int)irq7);
    set_idt_entry(40, (unsigned int)irq8);
    set_idt_entry(41, (unsigned int)irq9);
    set_idt_entry(42, (unsigned int)irq10);
    set_idt_entry(43, (unsigned int)irq11);
    set_idt_entry(44, (unsigned int)irq12);
    set_idt_entry(45, (unsigned int)irq13);
    set_idt_entry(46, (unsigned int)irq14);
    set_idt_entry(47, (unsigned int)irq15);

    // now that all idt entries are set, we can call lidtl
    idt_init();

    // all interrupt-handling is in place, can not restore interrupts
    __asm__ __volatile__("sti");
}

// will have additional functionality, eventually
void
isr_handler(regs_t registers)
{
    // global variables break for some reason...
    char *exception_messages[] = {
        "Division by zero",
        "Debug",
        "Non maskable interrupt",
        "Breakpoint",
        "Into detected overflow",
        "Out of bounds",
        "Invalid Opcode",
        "No coprocessor",
        "Double fault",
        "Coprocessor segment overrun",
        "Bad TSS",
        "Segment not present",
        "Stack fault",
        "General protection fault",
        "Page fault",
        "Unknown interrupt",
        "Coprocessor fault",
        "Alignment check",
        "Machine check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"
    };
    fb_write_str(5,0,"received interrupt: ", BLACK, WHITE);
    char str[3];
    d_str(registers.interrupt_num, str);
    fb_write_str(6,0, str, BLACK, WHITE);
    fb_write_str(7,0, exception_messages[registers.interrupt_num], BLACK, WHITE); // this isn't working...
}

void
register_interrupt_handler(unsigned char n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void
irq_handler(regs_t registers)
{
    if (registers.interrupt_num >= 40) outb(0xA0, 0x20);
    outb(0x20, 0x20);

    if (interrupt_handlers[registers.interrupt_num] != 0){
        isr_t handler = interrupt_handlers[registers.interrupt_num];
        handler(registers);
    }
}