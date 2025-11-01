#ifndef IDT_H
#define IDT_H
#define IDT_NULL (idt_entry_t){0, 0, 0, 0, 0}
typedef struct idt_entry
{
    unsigned short base_low;            // Low bits of base address (function pointer to ISR)
    unsigned short sel;                 // Address to Kernel base to pass control to kerne
    unsigned char reserved;             // Reserved by intel
    unsigned char flags;
    unsigned short base_high;           // High bits of base address 
 
}__attribute__((packed)) idt_entry_t;

typedef struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed)) idt_pointer_t;

idt_entry_t idt[256];       // 256 entry table of idt
idt_pointer_t p_idt;

extern void idt_load();
void set_idt_entry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void init_idt();
#endif

