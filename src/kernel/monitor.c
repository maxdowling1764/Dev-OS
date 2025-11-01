#include "monitor.h"

static terminal_context_t context;
static cursor_t cursor;

static terminal_context_t* p_context;

terminal_context_t* get_context()
{
    return p_context;
}

void init_monitor(char* vaddr)
{
    cursor.m_x = 0;
    cursor.m_y = 0;
    context.p_video_mem = vaddr;
    context.p_cursor = &cursor;
    p_context = &context;
}

char* get_vga_addr(int row, int col)
{
    return context.p_video_mem + 2*TERM_WIDTH*row + 2*col;
}

char* get_cursor_addr()
{
    return get_vga_addr(cursor.m_x, cursor.m_y);
}

void clear_term()
{
    char* curr_vga_addr = context.p_video_mem;
    for(int x = 0; x < TERM_HEIGHT; x++)
    {
        for(int y = 0; y < TERM_WIDTH; y++)
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
    char* src_vga_addr = context.p_video_mem;
    char* dest_vga_addr = src_vga_addr;

    for (int x = 1; x < TERM_HEIGHT; x++)
    {
        for (int y = 0; y < TERM_WIDTH; y++)
        {
            src_vga_addr = get_vga_addr(x, y);
            dest_vga_addr = get_vga_addr(x-1, y);
            *dest_vga_addr = *src_vga_addr;
            *(dest_vga_addr + 1) = *(src_vga_addr + 1);
        }
    }

    for (int y = 0; y < TERM_WIDTH; y++)
    {
        dest_vga_addr = get_vga_addr(TERM_HEIGHT-1, y);
        *dest_vga_addr = 0;
        *(dest_vga_addr + 1) = 0x0f;
    }
}

void print_str(const char* str, color_t back_color, color_t fore_color)
{
    int attr = (fore_color) | (back_color << 4);
    char* curr_vga_addr = context.p_video_mem;
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

void print_hex(unsigned short c, color_t back_color, color_t fore_color)
{    
    unsigned short curr_digit = c;          // Current digit aligned to the left
    print_str("0x", back_color, fore_color);
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
        putc(curr_hex, back_color, fore_color);
    }
}

void print_hex_int(unsigned int c, color_t back_color, color_t fore_color)
{    
    unsigned int curr_digit = c;          // Current digit aligned to the left
    print_str("0x", back_color, fore_color);
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
        putc(curr_hex, back_color, fore_color);
    }
}

void print_hex_byte(unsigned char c, color_t back_color, color_t fore_color)
{
    unsigned int curr_digit = c;          // Current digit aligned to the left
    char curr_hex = '0';
    for(int i = 0; i < 2; i++)
    {
        curr_digit = (c & 0xF0) >> 4;
        c = c << 4;

        if (curr_digit > 9)
        {
            curr_hex = 'A' + curr_digit - 10;
        }
        else
        {
            curr_hex = '0' + curr_digit;
        }
        putc(curr_hex, back_color, fore_color);
    }
}
void put_nibble(const char c, int radix, color_t back_color, color_t fore_color)
{
    if (radix >= sizeof(char)*2) return;
    char curr_hex = '0';
    char digit = (c & 0xF << radix*4) >> radix*4;
    if (digit > 9)
    {
        curr_hex = 'A' + digit - 10;
    }
    else
    {
        curr_hex = '0' + digit;
    }
    putc(curr_hex, back_color, fore_color);
}
void putc(const char c, color_t back_color, color_t fore_color)
{
    if (cursor.m_y >= TERM_WIDTH) 
    {
        cursor.m_y = 0;
        cursor.m_x++;
    }
    if(cursor.m_x >= TERM_HEIGHT)
    {
	cursor.m_x = TERM_HEIGHT-1;
	cursor.m_y = 0;
        scroll();
    }

    int attr = (fore_color) | (back_color << 4);

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

