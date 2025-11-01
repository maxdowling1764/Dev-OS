#ifndef IRQ_H
#define IRQ_H
#include "common.h"

void set_irq_handler(int idx, void (*handler)(regs_t* r));
void reset_irq_handler(int idx);
void remap_pic(void);
void init_irqs();
void init_irq_handler(int idx);
void irq_handler(regs_t* r);

#endif
