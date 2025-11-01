#ifndef MONITOR_H
#define MONITOR_H
#define TERM_WIDTH 80
#define TERM_HEIGHT 25
#define print_struct(s, a) for(unsigned int k = 0; k < sizeof(s); k++) { print_hex_int((unsigned int) (*(&a + k)), BLACK, LIGHT_GREEN); }
typedef enum color
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
} color_t;

typedef struct cursor
{
    int m_x;
    int m_y;
} cursor_t;

typedef struct terminal_context
{
    char* p_video_mem;
    cursor_t* p_cursor;
} terminal_context_t;


terminal_context_t* get_context();

void init_monitor(char* vaddr);
char* get_vga_addr(int row, int col);
char* get_cursor_addr();
void clear_term();
void scroll();
void print_str(const char* str, color_t back_color, color_t fore_color);
void putc(const char c, color_t back_color, color_t fore_color);
void print_hex(unsigned short c, color_t back_color, color_t fore_color);
void print_hex_byte(unsigned char c, color_t back_color, color_t fore_color);
void print_hex_int(unsigned int c, color_t back_color, color_t fore_color);
void put_nibble(const char c, int radix, color_t back_color, color_t fore_color);

#endif

