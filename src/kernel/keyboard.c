#include "monitor.h"
#include "common.h"

static void* key_handlers[128];
static unsigned int key_handles[128];
static unsigned int n_key_handles = 0;

static unsigned char keymap[128];

unsigned int add_key_handler(void (*handler)(unsigned int scancode))
{
    if (n_key_handles < 128)
    {
        key_handlers[n_key_handles] = handler;
	n_key_handles++;
    }
    return n_key_handles - 1;
}

void set_key_handler(unsigned int handle, void (*handler)(unsigned int scancode))
{
    key_handlers[handle] = handler;
}

unsigned char* get_keymap()
{
    return keymap;
}

void* get_key_handler(unsigned int handle)
{
    if (handle == 0)
    {
        return (void*)0;
    }

    if (handle < n_key_handles)
    {
        return key_handlers[handle];
    }
}

void keyboard_handler(t_regs* r)
{
    unsigned char scancode;
    scancode = inportb(0x60);

    if (scancode & 0x80)
    {
    }
    else
    {
        void (*tmp_handler)(unsigned int) = key_handlers[scancode];
	if (tmp_handler == 0)
	{
            putc(keymap[scancode], BLACK, LIGHT_GREEN);
	}
	else
        {
            tmp_handler(scancode);
        }
    }   
}
