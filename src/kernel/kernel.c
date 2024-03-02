#include "monitor.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "gdt.h"
#include "common.h"
#include "keyboard.h"

#define MMAP_OFFSET 0x1000

// sizeof(uint64) = 32 + 32 = 64 bits = 8 bytes
typedef struct t_uint64{
	unsigned int low; 
	unsigned int high;
} uint64;

void put0x_uInt64(uint64 a)
{
	put0xInt(a.low, BLACK, YELLOW);
	put0xInt(a.high, BLACK, CYAN);
}

// sizeof(MemMapEntry) = 2 * sizeof(uint64) = 16 bytes;
// + 2 * sizeof(uint32) = 8 bytes = 24 bytes;
typedef struct {
	uint64 base;
	uint64 limit;
	unsigned int type;
	unsigned int ext;
} MemMapEntry;

void print_mmap_entry(MemMapEntry* mmap, char* tab)
{
		print_str(" Base: \0", BLACK, YELLOW);
		put0x_uInt64(mmap->base); // Print Base
		print_str(" | Limit: \0", BLACK, YELLOW);
		put0x_uInt64(mmap->limit); // Print Limit
	putc('\n', BLACK, YELLOW);
		print_str(tab, BLACK, YELLOW);
		print_str("Type: \0", BLACK, YELLOW);
		put0xInt(mmap->type, BLACK, CYAN);
		print_str(" | Extended: \0", BLACK, YELLOW);
		put0xInt(mmap->ext, BLACK, CYAN);       // Print Extension
	putc('\n', BLACK, YELLOW);
}

void print_mmap(unsigned int count)
{
	MemMapEntry* mmap = (MemMapEntry*)MMAP_OFFSET;
	clear_term();
	char* header = "Printing mmap\n\0";
	char* msg2 = "offset \0";
	char* tab =  "                    \0";
	print_str(header, BLACK, YELLOW);
	for(unsigned int i = 0; i < count; i++)
	{
		print_str(msg2, BLACK, YELLOW);
		put0xInt(i, BLACK, GREEN);			// Print iteration count
		putc(' ', BLACK, GREEN);
		putc(':', BLACK, GREEN);
		print_mmap_entry(mmap, tab);

		mmap = (MemMapEntry*)(mmap + i);
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
    
    t_p_gdt gdt_ptr = init_gdt();
    init_idt();
    init_isr();
    init_irqs();
    set_irq_handler(1, keyboard_handler);
    print_mmap(11);
    for(;;)
    {
    } 
}


