#ifndef GDT_H
#define GDT_H
#define GDTPTR_OFFSET 0x1000

typedef struct gdt_entry
{
    unsigned short limit;       // Size of segment
    unsigned short base_lo;     // bits 0-15 of segment location
    unsigned char base_mid;     // bits 16-23 of segment location
    unsigned char type_flags;   // type of segment
    unsigned char limit_flags;  // ???
    unsigned char base_hi;      // bits 24-32 of segment location
}__attribute__((packed)) t_gdt_entry;

t_gdt_entry get_gdt_entry(int idx);

typedef struct gdt_desc
{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed)) t_gdt_desc;

typedef struct gdt_desc_unpacked
{
    unsigned short limit;
    unsigned int base;
} t_gdt_desc_unpacked;

void init_gdt();
t_gdt_desc get_gdt_desc();
void set_gdt_entry(int idx, t_gdt_entry* entry);
#endif