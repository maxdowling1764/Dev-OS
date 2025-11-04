#include "monitor.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "gdt.h"
#include "common.h"
#include "keyboard.h"
#include "mmap.h"

#define offsetof(st, m) \
    ((unsigned int)&(((st*)0)->m))

void print_mmap_entry(e820_entry_t entry)
{
    print_hex_int(entry.base_hi, BLACK, LIGHT_GREEN);
    putc(' ', BLACK, LIGHT_GREEN);
    print_hex_int(entry.base_low, BLACK, LIGHT_GREEN);
    print_str(" || ", BLACK, LIGHT_GREEN);
    print_hex_int(entry.lim_hi, BLACK, LIGHT_GREEN);
    putc(' ', BLACK, LIGHT_GREEN);
    print_hex_int(entry.lim_low, BLACK, LIGHT_GREEN);
    putc('\n', BLACK, LIGHT_GREEN);
}

void print_mmap()
{
    print_str("MMAP BASE_HI BASE_LOW || LIM_HI LIM_LOW\n", BLACK, LIGHT_GREEN);
    for (unsigned int i = 0; i < mmap_get_count(); i++)
    {
        print_mmap_entry(mmap_get_entry(i));
    }
}

void print_gdt_entry(gdt_entry_t* a)
{
    for(unsigned int k = 0; k < sizeof(gdt_entry_t); k++) 
    { 
        print_hex_byte((*((unsigned char*)a + k)), BLACK, LIGHT_GREEN);
        putc(' ', BLACK, LIGHT_GREEN);
    }
    print_str("||", BLACK, LIGHT_GREEN);
    print_str("LIM: ", BLACK, LIGHT_GREEN);
    unsigned int k = 0;
    for(; k < sizeof(unsigned short); k++) 
    { 
        print_hex_byte((*((unsigned char*)a + k)), BLACK, LIGHT_GREEN);
    }
    int k0 = offsetof(gdt_entry_t, limit_flags);
    put_nibble(a->limit_flags, 0, BLACK, LIGHT_GREEN);
    putc('\n', BLACK, LIGHT_GREEN);
}
void print_gdt(gdt_pointer_t* gdt_ptr)
{
    print_str("GDTPTR OFFSET: ", BLACK, LIGHT_GREEN);
    print_hex_int(GDTPTR_OFFSET, BLACK, LIGHT_GREEN);
    print_str("\n-------------\n", BLACK, LIGHT_GREEN); 
    
    for(int i = 0; i < gdt_ptr->num_entries; i++)
    {
	print_gdt_entry(&gdt_ptr->p_entries[i]);
    }
}
void main()
{
    unsigned char kbdus[128] = 
    {
        0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
    '9', '0', '-', '=', '\b',	/* Backspace */
    '\t',			/* Tab */
    'q', 'w', 'e', 'r',	/* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
        0,			/* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
    '\'', '`',   0,		/* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
    'm', ',', '.', '/',   0,				/* Right shift */
    '*',
        0,	/* Alt */
    ' ',	/* Space bar */
        0,	/* Caps lock */
        0,	/* 59 - F1 key ... > */
        0,   0,   0,   0,   0,   0,   0,   0,
        0,	/* < ... F10 */
        0,	/* 69 - Num lock*/
        0,	/* Scroll Lock */
        0,	/* Home key */
        0,	/* Up Arrow */
        0,	/* Page Up */
    '-',
        0,	/* Left Arrow */
        0,
        0,	/* Right Arrow */
    '+',
        0,	/* 79 - End key*/
        0,	/* Down Arrow */
        0,	/* Page Down */
        0,	/* Insert Key */
        0,	/* Delete Key */
        0,   0,   0,
        0,	/* F11 Key */
        0,	/* F12 Key */
        0,	/* All other keys are undefined */
    };

    arr_copy(kbdus, get_keymap(), 128);
    char* video_mem = (char*) 0xb8000;
    char* k_start_msg = "Started Kernel\n\0";
    init_monitor(video_mem); 
    //clear_term();
    print_str(k_start_msg, BLACK, LIGHT_GREEN);
    
    gdt_pointer_t gdt_ptr = init_gdt();
    init_idt();
    init_isr();
    init_irqs();
    set_irq_handler(1, keyboard_handler);
    print_gdt(&gdt_ptr);
    print_mmap();   
 

    
    for(;;)
    {
    } 
}

