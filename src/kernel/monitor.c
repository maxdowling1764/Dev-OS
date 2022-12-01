#include "monitor.h"

char* get_vga_addr(char* video_mem, int row, int col)
{
    return video_mem + 2*80*row + 2*col;
}

char* get_cursor_addr(char* video_mem, t_Cursor* p_cursor)
{
    return get_vga_addr(video_mem, p_cursor->m_x, p_cursor->m_y);
}

void clear_term(t_TermCTX* context)
{
    char* curr_vga_addr = context->m_video_mem;
    for(int x = 0; x < 25; x++)
    {
        for(int y = 0; y < 80; y++)
        {
            curr_vga_addr = get_vga_addr(context->m_video_mem, x, y);
            *curr_vga_addr = 0;
            *(curr_vga_addr + 1) = 0x0f;
        }
    }
}

void scroll(t_TermCTX* context)
{
    char* src_vga_addr = context->m_video_mem;
    char* dest_vga_addr = src_vga_addr;

    for (int x = 1; x < 24; x++)
    {
        for (int y = 0; y < 80; y++)
        {
            src_vga_addr = get_vga_addr(context->m_video_mem, x, y);
            dest_vga_addr = get_vga_addr(context->m_video_mem, x-1, y);
            *dest_vga_addr = *src_vga_addr;
            *(dest_vga_addr + 1) = *(src_vga_addr + 1);
        }
    }

    for (int y = 0; y < 80; y++)
    {
        dest_vga_addr = get_vga_addr(context->m_video_mem, 25, y);
        *dest_vga_addr = 0;
        *(dest_vga_addr + 1) = 0x0f;
    }
}

void print_str(char* str, t_TermCTX* context, unsigned char backColor, unsigned char foreColor)
{
    int attr = (foreColor) | (backColor << 4);
    char* curr_vga_addr = context->m_video_mem;
    while(*str)
    {
        if(*str == '\n')
        {
            context->m_cursor->m_x = context->m_cursor->m_x + 1;
            context->m_cursor->m_y = 0;
        }
        else
        {
            curr_vga_addr = get_cursor_addr(context->m_video_mem, context->m_cursor);
            *curr_vga_addr = *str;
            curr_vga_addr++;
            *curr_vga_addr = attr;
            context->m_cursor->m_y = context->m_cursor->m_y + 1;
        }
        str++;
    }
}


