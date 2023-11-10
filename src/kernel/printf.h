#define VGA_START 0xb8000
#define va_arg(list, type) ( (type*) ( list = (char*) list + sizeof(type) ) )[-1]

enum color
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
    WHITE,
};

void vga_print_char(char symbol, int x, int y, int foreground_color);

void vga_clear_screen();

void vga_print_string(char* str, int x, int y, int text_color);

void shift_up();

void init_printer();

void end_line();

void print_char(char s, int color);

void print_string(char* str, int color);

void printf(char *fmt, ...);