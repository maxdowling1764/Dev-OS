#ifndef MONITOR_H
#define MONITOR_H
#define TERM_WIDTH 80
#define TERM_HEIGHT 25
#define print_struct(s, a) for(unsigned int k = 0; k < sizeof(s); k++) { print_hex_int((unsigned int) (*(&a + k)), BLACK, LIGHT_GREEN); }
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


t_TermCTX* get_context();

void init_monitor(char* vaddr);
char* get_vga_addr(int row, int col);
char* get_cursor_addr();
void clear_term();
void scroll();
void print_str(const char* str, unsigned char backColor, unsigned char foreColor);
void putc(const char c, unsigned char backColor, unsigned char foreColor);
void print_hex(unsigned short c, unsigned char backColor, unsigned char foreColor);
void print_hex_byte(unsigned char c, unsigned char backColor, unsigned char foreColor);
void print_hex_int(unsigned int c, unsigned char backColor, unsigned char foreColor);
void put_nibble(const char c, int radix, unsigned char backColor, unsigned char foreColor);

#endif

