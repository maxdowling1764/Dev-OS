#ifndef MONITOR_H
#define MONITOR_H
enum Colors
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    PURPLE,
    BROWN,
    GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_PURPLE,
    YELLOW,
    WHITE
};

typedef struct Cursor
{
    int m_x;
    int m_y;
} t_Cursor;

typedef struct TermCTX
{
    char* m_video_mem;
    t_Cursor m_cursor;
} t_TermCTX;


void init_monitor(char* vaddr);
char* get_vga_addr(int row, int col);
char* get_cursor_addr();
void clear_term();
void scroll();
void print_str(const char* str, unsigned char backColor, unsigned char foreColor);
void putc(const char c, unsigned char backColor, unsigned char foreColor);
void put0xShort(unsigned short c, unsigned char backColor, unsigned char foreColor);
void put0xInt(unsigned int c, unsigned char backColor, unsigned char foreColor);

#endif
