#ifndef MMAP_H
#define MMAP_H
#define MMAP_OFFSET 0x08000

typedef struct e820_entry
{
	unsigned int base_low;
	unsigned int base_hi;
	unsigned int lim_low;
	unsigned int lim_hi;
	unsigned int type;
	unsigned int attrs;
}__attribute__((packed)) e820_entry_t;

unsigned int mmap_get_count();
e820_entry_t mmap_get_null();
e820_entry_t mmap_get_entry(unsigned int i);
#endif
