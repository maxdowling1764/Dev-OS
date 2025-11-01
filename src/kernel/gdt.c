#include "gdt.h"

gdt_pointer_t init_gdt()
{
    gdt_descriptor_t* p_desc =(gdt_descriptor_t*)GDTPTR_OFFSET; 
    return (gdt_pointer_t) {
	    .p_desc=p_desc, 
	    .p_entries=(gdt_entry_t*)(p_desc->base), 
	    .num_entries=(p_desc->limit/sizeof(gdt_entry_t))};
}

gdt_entry_t get_gdt_entry(const int idx, const gdt_pointer_t* gdt)
{
    if(idx < gdt->num_entries)
    {
        return gdt->p_entries[idx];
    }
    return (gdt_entry_t){.base_hi = 0, .base_lo = 0, .base_mid = 0, .limit =0, .limit_flags = 0, .type_flags = 0};
}

void set_gdt_entry(const int idx, const gdt_pointer_t* gdt, const gdt_entry_t* entry)
{
    if(idx < gdt->num_entries)
    {
        gdt->p_entries[idx] = *entry;
    }
}
