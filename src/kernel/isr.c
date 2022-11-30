#include "isr.h"
#define INIT_ISR(num) \
    set_idt_entry(num, (unsigned long) isr##num, 0x08, 0x8E);

void init_isr()
{
    INIT_ISR(0);
    INIT_ISR(1);
    INIT_ISR(2);
    INIT_ISR(3);
    INIT_ISR(4);
    INIT_ISR(5);
    INIT_ISR(6);
    INIT_ISR(7);
    INIT_ISR(8);
    INIT_ISR(9);
    INIT_ISR(10);
    INIT_ISR(11);
    INIT_ISR(12);
    INIT_ISR(13);
    INIT_ISR(14);
    INIT_ISR(15);
    INIT_ISR(16);
    INIT_ISR(17);
    INIT_ISR(18);
    INIT_ISR(19);
    INIT_ISR(20);
    INIT_ISR(21);
    INIT_ISR(22);
    INIT_ISR(23);
    INIT_ISR(24);
    INIT_ISR(25);
    INIT_ISR(26);
    INIT_ISR(27);
    INIT_ISR(28);
    INIT_ISR(29);
    INIT_ISR(30);
    INIT_ISR(31);
}

void irq_handler(t_regs* r)
{
    return;
}

void fault_handler(t_regs* r)
{
    if (r->int_code < 32)
    {
        // TODO Import Print String from refactored vga.h
        
        while(1==1)
        {
            // Hang on fault
        }
    }
}
