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
}__attribute__((packed)) t_gdt_entry;

typedef struct gdt_desc
{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed)) t_gdt_desc;

typedef struct p_gdt
{
    t_gdt_desc* p_desc;
    t_gdt_entry* p_entries;
    unsigned int num_entries;
} t_p_gdt;

t_p_gdt init_gdt();
t_gdt_entry get_gdt_entry(int idx, const t_p_gdt* gdt);
void set_gdt_entry(const int idx, const t_p_gdt* gdt, const t_gdt_entry* entry);
#endif
