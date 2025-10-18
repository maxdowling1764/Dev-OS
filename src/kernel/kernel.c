#include "monitor.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "gdt.h"
#include "common.h"
#include "keyboard.h"


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
    
    t_p_gdt gdt_ptr = init_gdt();
    init_idt();
    init_isr();
    init_irqs();
    set_irq_handler(1, keyboard_handler);
    
    t_gdt_entry d = get_gdt_entry(1, &gdt_ptr);
    t_gdt_entry d2 = get_gdt_entry(2, &gdt_ptr);
    print_hex(d.limit, BLACK, RED);
    print_hex(d2.limit, BLACK, GREEN);
    for(;;)
    {
    } 
}

