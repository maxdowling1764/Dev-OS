#ifndef IRQ_H
#define IRQ_H
#include "common.h"

#define DECL_IRQ(num)\
    extern void irq##num()

DECL_IRQ(0);
DECL_IRQ(1);
DECL_IRQ(2);
DECL_IRQ(3);
DECL_IRQ(4);
DECL_IRQ(5);
DECL_IRQ(6);
DECL_IRQ(7);
DECL_IRQ(8);
DECL_IRQ(9);
DECL_IRQ(10);
DECL_IRQ(11);
DECL_IRQ(12);
DECL_IRQ(13);
DECL_IRQ(14);
DECL_IRQ(15);

void set_irq_handler(int idx, void (*handler)(t_regs* r));
void reset_irq_handler(int idx);
void remap_pic(void);
void init_irqs();
void init_irq_handler(int idx);
void irq_handler(t_regs* r);

#endif
