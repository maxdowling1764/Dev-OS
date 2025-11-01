#include "mmap.h"

unsigned int mmap_get_count()
{
    return *((unsigned int*) MMAP_OFFSET);
}

e820_entry_t mmap_get_null()
{
    return (e820_entry_t) 
    {
        .base_low=0, 
        .base_hi=0, 
        .lim_low=0, 
        .lim_hi=0, 
        .type=0, 
        .attrs=0
    };
}

e820_entry_t mmap_get_entry(unsigned int i)
{
    if (i < mmap_get_count())
        return *((e820_entry_t*)(MMAP_OFFSET + sizeof(e820_entry_t)*i + sizeof(unsigned int)));
    else return mmap_get_null();
}
