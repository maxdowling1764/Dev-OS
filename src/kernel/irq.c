#include "irq.h"
#include "idt.h"
#include "monitor.h"

#define INIT_IRQ(num) \
    set_idt_entry(num + 32, (unsigned long) irq##num, 0x08, 0x8E)

static void* irq_handlers[16];



void init_irqs()
{
    for (int i = 0; i < 16; i++)
    {
        init_irq_handler(i);
    }
    remap_pic();
    INIT_IRQ(0);
    INIT_IRQ(1);
    INIT_IRQ(2);
    INIT_IRQ(3);

    INIT_IRQ(4);
    INIT_IRQ(5);
    INIT_IRQ(6);
    INIT_IRQ(7);
      
    INIT_IRQ(8);
    INIT_IRQ(9);
    INIT_IRQ(10);
    INIT_IRQ(11);

    INIT_IRQ(12);
    INIT_IRQ(13);
    INIT_IRQ(14);
    INIT_IRQ(15);
    print_str("Initialized IRQs\n\0", BLACK, GREEN);
}
void remap_pic(void)
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

void set_irq_handler(int idx, void (*handler)(t_regs* r))
{
    irq_handlers[idx] = handler;
}

void init_irq_handler(int idx)
{
    irq_handlers[idx] = 0;
}

void irq_handler(t_regs* r)
{
    void (*handler)(t_regs* r);
    handler = irq_handlers[r->int_code - 32];
    print_str("IRQ Triggered\n\0", BLACK, GREEN);
    if (handler)
    {
        handler(r);
    }

    if (r->int_code >= 40)
    {
        outportb(0xA0, 0x20);
    }

    outportb(0x20, 0x20);
}
