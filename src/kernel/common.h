#ifndef COMMON_H
#define COMMON_H
typedef struct regs 
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_code, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
} t_regs;

void arr_copy(unsigned char* src, unsigned char* dest, int size);
void outportb(unsigned short port, unsigned char data);
unsigned char inportb(unsigned short port);
#endif
