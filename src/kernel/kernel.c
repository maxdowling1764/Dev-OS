#include "monitor.h"
#include "idt.h"
#include "isr.h"

void main()
{
    char* video_mem = (char*) 0xb8000;
    char* k_start_msg = "started Kernel\n\0";
    init_monitor(video_mem); 
    clear_term();
    print_str(k_start_msg, BLACK, LIGHT_GREEN);
    init_idt();
    init_isr();
    int x = 10 / 0;
}
