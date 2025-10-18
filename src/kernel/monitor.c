#include "monitor.h"

static t_TermCTX context;
static t_Cursor cursor;

static t_TermCTX* p_context;

t_TermCTX* get_context()
{
    return p_context;
}

void init_monitor(char* vaddr)
{
    cursor.m_x = 0;
    cursor.m_y = 0;
    context.m_video_mem = vaddr;
    context.m_cursor = &cursor;
    p_context = &context;
}

char* get_vga_addr(int row, int col)
{
    return context.m_video_mem + 2*80*row + 2*col;
}

char* get_cursor_addr()
{
    return get_vga_addr(cursor.m_x, cursor.m_y);
}

void clear_term()
{
    char* curr_vga_addr = context.m_video_mem;
    for(int x = 0; x < 25; x++)
    {
        for(int y = 0; y < 80; y++)
        {
            curr_vga_addr = get_vga_addr(x, y);
            *curr_vga_addr = 0;
            *(curr_vga_addr + 1) = 0x0f;
        }
    }
    cursor.m_x = 0;
    cursor.m_y = 0;
}

void scroll()
{
    char* src_vga_addr = context.m_video_mem;
    char* dest_vga_addr = src_vga_addr;

    for (int x = 1; x < 24; x++)
    {
        for (int y = 0; y < 80; y++)
        {
            src_vga_addr = get_vga_addr(x, y);
            dest_vga_addr = get_vga_addr(x-1, y);
            *dest_vga_addr = *src_vga_addr;
            *(dest_vga_addr + 1) = *(src_vga_addr + 1);
        }
    }

    for (int y = 0; y < 80; y++)
    {
        dest_vga_addr = get_vga_addr(25, y);
        *dest_vga_addr = 0;
        *(dest_vga_addr + 1) = 0x0f;
    }
}

void print_str(const char* str, unsigned char backColor, unsigned char foreColor)
{
    int attr = (foreColor) | (backColor << 4);
    char* curr_vga_addr = context.m_video_mem;
    char* curr_char = str;

    while(*curr_char)
    {
        if(*curr_char == '\n')
        {
            cursor.m_x++;
            cursor.m_y = 0;
        }
        else
        {
            curr_vga_addr = get_cursor_addr();
            *curr_vga_addr = *curr_char;
            curr_vga_addr++;
            *curr_vga_addr = attr;
            cursor.m_y++;
        }
        curr_char++;
    }
}

void print_hex(unsigned short c, unsigned char backColor, unsigned char foreColor)
{    
    unsigned short curr_digit = c;          // Current digit aligned to the left
    char curr_hex = '0';
    for(int i = 0; i < 4; i++)
    {
        curr_digit = (c & 0xF000) >> 12;
        c = c << 4;

        if (curr_digit > 9)
        {
            curr_hex = 'A' + curr_digit - 10;
        }
        else
        {
            curr_hex = '0' + curr_digit;
        }
        putc(curr_hex, backColor, foreColor);
    }
}

void print_hex_int(unsigned int c, unsigned char backColor, unsigned char foreColor)
{    
    unsigned int curr_digit = c;          // Current digit aligned to the left
    char curr_hex = '0';
    for(int i = 0; i < 8; i++)
    {
        curr_digit = (c & 0xF0000000) >> 28;
        c = c << 4;

        if (curr_digit > 9)
        {
            curr_hex = 'A' + curr_digit - 10;
        }
        else
        {
            curr_hex = '0' + curr_digit;
        }
        putc(curr_hex, backColor, foreColor);
    }
}


void putc(const char c, unsigned char backColor, unsigned char foreColor)
{
    int attr = (foreColor) | (backColor << 4);

    char* curr_vga_addr = get_cursor_addr();

    if(c == '\n')
    {
        cursor.m_x++;
        cursor.m_y = 0;
    }
    else
    {
        *curr_vga_addr = c;
        *(curr_vga_addr + 1) = attr;
        cursor.m_y++;
    }    
}


