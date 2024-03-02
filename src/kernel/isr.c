#include "isr.h"

#include "idt.h"
#include "monitor.h"

#define INIT_ISR(num) \
    set_idt_entry(num, (unsigned long) isr##num, 0x08, 0x8E)

#define SET_EXC_MSG(num, msg) \
    exception_msgs[num]= msg

#define GENERAL_EXC_MSG "Unhandled Exception: "

static char* exception_msgs[32]; 

void init_isr()
{
    SET_EXC_MSG(0, "Div by Zero\0");
    SET_EXC_MSG(1, "Debug\0");
    SET_EXC_MSG(2, "NMI\0");
    SET_EXC_MSG(3, "Breakpoint\0");
    SET_EXC_MSG(4, "Overflow\0");
    SET_EXC_MSG(5, "Out of Bounds\0");
    SET_EXC_MSG(6, "Invalid Opcode\0");
    SET_EXC_MSG(7, "No Coprocessor\0");
    SET_EXC_MSG(8, "Double Fault\0");
    SET_EXC_MSG(9, "Coprocessor Segment Overrun\0");
    SET_EXC_MSG(10, "Bad TSS\0");
    SET_EXC_MSG(11, "Segment Not Present\0");
    SET_EXC_MSG(12, "Stack Fault\0");
    SET_EXC_MSG(13, "General Protection\0");
    SET_EXC_MSG(14, "Page Fault\0");
    SET_EXC_MSG(15, "Unknown Interrupt\0");
    SET_EXC_MSG(16, "Coprocessor Fault\0");
    SET_EXC_MSG(17, "Alignment Check\0");
    SET_EXC_MSG(18, "Machine Check\0");
    SET_EXC_MSG(19, "Reserved\0");
    SET_EXC_MSG(20, "Reserved\0");
    SET_EXC_MSG(21, "Reserved\0");
    SET_EXC_MSG(22, "Reserved\0");
    SET_EXC_MSG(23, "Reserved\0");
    SET_EXC_MSG(24, "Reserved\0");
    SET_EXC_MSG(25, "Reserved\0");
    SET_EXC_MSG(26, "Reserved\0");
    SET_EXC_MSG(27, "Reserved\0");
    SET_EXC_MSG(28, "Reserved\0");
    SET_EXC_MSG(29, "Reserved\0");
    SET_EXC_MSG(30, "Reserved\0");
    SET_EXC_MSG(31, "Reserved\0");
    INIT_ISR(0);
    INIT_ISR(1);
    INIT_ISR(2);
    INIT_ISR(3);
    INIT_ISR(4);
    INIT_ISR(5);
    INIT_ISR(6);
    INIT_ISR(7);
    INIT_ISR(8);
    INIT_ISR(9);
    INIT_ISR(10);
    INIT_ISR(11);
    INIT_ISR(12);
    INIT_ISR(13);
    INIT_ISR(14);
    INIT_ISR(15);
    INIT_ISR(16);
    INIT_ISR(17);
    INIT_ISR(18);
    INIT_ISR(19);
    INIT_ISR(20);
    INIT_ISR(21);
    INIT_ISR(22);
    INIT_ISR(23);
    INIT_ISR(24);
    INIT_ISR(25);
    INIT_ISR(26);
    INIT_ISR(27);
    INIT_ISR(28);
    INIT_ISR(29);
    INIT_ISR(30);
    INIT_ISR(31);
}

void fault_handler(t_regs* r)
{
    if (r->int_code < 32)
    {
        // TODO Import Print String from refactored vga.h
        print_str(GENERAL_EXC_MSG, BLACK, RED);
        print_str(exception_msgs[r->int_code], BLACK, RED);
        char* hang_msg = "\nHanging...\n\0";
        print_str(hang_msg, BLACK, RED);
        while(1==1)
        {
            // Hang on fault
        }
    }
}
