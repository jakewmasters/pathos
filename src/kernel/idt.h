/*
 * IDT entry
 * will ultimately be 256 of these
 */
typedef struct {
    unsigned short offset_low;
    unsigned short selector; 
    unsigned char zero; // always zero
    unsigned char type; 
    unsigned short offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) idt_descriptor_t;

#define IDT_ENTRIES 256
idt_entry_t idt[IDT_ENTRIES];
idt_descriptor_t idt_desc;

extern void idt_init();
extern void set_idt_entry(int i, unsigned int handler);
