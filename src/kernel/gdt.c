#include "gdt.h"

static t_gdt_desc* p_gdt_desc;
static t_gdt_entry* gdt_entries;
static int num_gdt_entries;

void init_gdt()
{
    p_gdt_desc = (t_gdt_desc*) GDTPTR_OFFSET;

    t_gdt_desc desc = get_gdt_desc();
    gdt_entries = (t_gdt_entry*) desc.base;
    num_gdt_entries = desc.limit / sizeof(t_gdt_entry);
}

t_gdt_desc get_gdt_desc()
{
    return *p_gdt_desc;
}

t_gdt_entry get_gdt_entry(int idx)
{
    if(idx < num_gdt_entries)
    {
        return gdt_entries[idx];
    }
    return (t_gdt_entry){.base_hi = 0, .base_lo = 0, .base_mid = 0, .limit =0, .limit_flags = 0, .type_flags = 0};
}

void set_gdt_entry(int idx, t_gdt_entry* entry)
{
    if(idx < num_gdt_entries)
    {
        gdt_entries[idx] = *entry;
    }
}