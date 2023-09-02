#include "gdt.h"

t_p_gdt init_gdt()
{
    t_gdt_desc* p_desc =(t_gdt_desc*)GDTPTR_OFFSET; 
    return (t_p_gdt) {
	    .p_desc=p_desc, 
	    .p_entries=(t_gdt_entry*)(p_desc->base), 
	    .num_entries=(p_desc->limit/sizeof(t_gdt_entry))};
}

t_gdt_entry get_gdt_entry(const int idx, const t_p_gdt* gdt)
{
    if(idx < gdt->num_entries)
    {
        return gdt->p_entries[idx];
    }
    return (t_gdt_entry){.base_hi = 0, .base_lo = 0, .base_mid = 0, .limit =0, .limit_flags = 0, .type_flags = 0};
}

void set_gdt_entry(const int idx, const t_p_gdt* gdt, const t_gdt_entry* entry)
{
    if(idx < gdt->num_entries)
    {
        gdt->p_entries[idx] = *entry;
    }
}
