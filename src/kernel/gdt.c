#include "gdt.h"

static t_gdt_desc* p_gdt_desc;

void init_gdt()
{
    p_gdt_desc = (t_gdt_desc*) GDTPTR_OFFSET;
}

t_gdt_desc get_gdt_desc()
{
    return *p_gdt_desc;
}