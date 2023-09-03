#pragma once
#include "common.h"

unsigned char* get_keymap();
unsigned int add_key_handler(void (*handler)(unsigned int scancode));
void set_key_handler(unsigned int loc, void (*handler)(unsigned int scancode));
void* get_key_handler(unsigned int handle);
void keyboard_handler(t_regs* r);
