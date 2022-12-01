#include "monitor.h"

void main()
{
    char* video_mem = (char*) 0xb8000;
    char* test = "Test\nTest\0";
    cursor.m_x = 0;
    cursor.m_y = 0;
    context.m_video_mem = video_mem;
    context.m_cursor = &cursor;
    clear_term(&context);
    print_str(test, &context, BLACK, YELLOW);
    scroll(&context);
}
