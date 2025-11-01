#pragma once
#include "common.h"

typedef struct {
	void* key_handlers[128];
	unsigned int key_handles[128];
	unsigned int n_key_handles;

	unsigned char keymap[128];

} KeyboardConfig;

unsigned char* get_keymap();
unsigned int add_key_handler(void (*handler)(unsigned int scancode));
void set_key_handler(unsigned int loc, void (*handler)(unsigned int scancode));
void* get_key_handler(unsigned int handle);
void keyboard_handler(regs_t* r);
