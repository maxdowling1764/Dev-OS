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
    t_Cursor* m_cursor;
} t_TermCTX;

char* get_vga_addr(char* video_mem, int row, int col);
char* get_cursor_addr(char* video_mem, t_Cursor* p_cursor);
void clear_term(t_TermCTX* context);
void scroll(t_TermCTX* context);
void print_str(char* str, t_TermCTX* context, unsigned char backColor, unsigned char foreColor);
#endif
