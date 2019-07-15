extern void isr0();
extern void isr1();
extern void isr2();

// binding all registers to struct to make functions easier
typedef struct {
    unsigned int ds;
    unsigned int eax, ebx, ecx, edx, esi, edi, ebp, esp;
    unsigned int interrupt_num, error_code;
    unsigned int eip, cs, eflags, useresp, ss;
} regs_t;

void isrs_init();
void isr_handler(regs_t registers);