#include "idt.h"

void set_idt_entry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num] = 
    (idt_entry_t){
        .base_low   = 0xFFFF & base, 
        .sel        = sel,
        .reserved   = 0,
        .flags      = flags,
        .base_high  = 0xFFFF & (base >> 16)
    };
}

void init_idt()
{
    p_idt = 
    (idt_pointer_t){
        .limit  = (sizeof (idt_entry_t) * 256) - 1,
        .base   = &idt,
    }; 

    for (int i = 0; i < 256; i++)
    {
        idt[i] = IDT_NULL;
    }
    idt_load();
}

