#include "monitor.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "common.h"

static unsigned char keymap[128];

void keyboard_handler(t_regs* r)
{
    unsigned char scancode;
    scancode = inportb(0x60);

    if (scancode & 0x80)
    {
    }
    else
    {
        putc(keymap[scancode], BLACK, LIGHT_GREEN);
    }   
}

void arr_copy(unsigned char* src, unsigned char* dest, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(dest+i) = *(src+i);
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
    arr_copy(kbdus, keymap, 128);
    char* video_mem = (char*) 0xb8000;
    char* k_start_msg = "Started Kernel\n\0";
    init_monitor(video_mem); 
    //clear_term();
    print_str(k_start_msg, BLACK, LIGHT_GREEN);
    init_idt();
    init_isr();
    init_irqs();
    set_irq_handler(1, keyboard_handler);
    unsigned short* gdt_ptr = 0x1000;
    print_hex(*(gdt_ptr), BLACK, YELLOW);
    for(;;)
    {
    } 
}
