#ifndef GDT_H
#define GDT_H
#define GDTPTR_OFFSET 0x10C02

typedef struct gdt_entry
{
    /* Note: limit_flags desc is listed in order of LSBs to MSBs */
    unsigned short limit;       // bit 0-15 of limit
    unsigned short base_lo;     // bits 0-15 of base 
    unsigned char base_mid;     // bits 16-23 of base
    unsigned char type_flags;   // type of segment
    unsigned char limit_flags;  // bits 16-20 of limit and flags 
    unsigned char base_hi;      // bits 24-32 of segment location
}__attribute__((packed)) gdt_entry_t;

typedef struct gdt_descriptor
{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed)) gdt_descriptor_t;

typedef struct gdt_pointer
{
    gdt_descriptor_t* p_desc;
    gdt_entry_t* p_entries;
    unsigned int num_entries;
} gdt_pointer_t;

gdt_pointer_t init_gdt();
gdt_entry_t get_gdt_entry(int idx, const gdt_pointer_t* gdt);
void set_gdt_entry(const int idx, const gdt_pointer_t* gdt, const gdt_entry_t* entry);
#endif
