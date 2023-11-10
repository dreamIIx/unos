#include "printf.h"

static int current_x; 
static int current_y;

void vga_print_char(char symbol, int x, int y, int foreground_color) {
    if (x >= 80 || y >= 25) return;
    *((short *)(VGA_START + 2 * (y * 80 + x))) = ((short) foreground_color) << 8 | (short) symbol;
}

void vga_clear_screen() {
    memzero((void*)VGA_START, sizeof(short) * 25 * 80);
}

void vga_print_string(char* str, int x, int y, int text_color) {
    int current_x = x;
    int current_y = y;
    int shift = 0;
    while (str[shift]) {
        vga_print_char(str[shift++], current_x++, current_y, text_color);
        if (current_x >= 80) {
            end_line();
        }
    }
}

void shift_up() {
    memcpy(VGA_START, VGA_START + sizeof(short) * 80, sizeof(short) * 24 * 80);
    memzero(VGA_START + sizeof(short) * 80 * 24, sizeof(short) * 80);
}

void init_printer() {
    current_x = 0;
    current_y = 0;
    vga_clear_screen();
}

void end_line() {
    if (current_y > 25) shift_up();
    else                ++current_y;
    current_x = 0;
}

void print_char(char s, int color) {
    vga_print_char(s, current_x, current_y, color);
    if (++current_x == 80) end_line();
}

void print_string(char* str, int color) {
    while (*str) {
        print_char(*str, color);
        ++str;
    }
}

void printf(char* fmt, ...) {
    va_list a = va_start(fmt);
    for (char* i = fmt; *i; ++i) {
        if (*i == '%') {
            if (*(i + 1) == '%') {
                print_char('%', WHITE);
                ++i;
            } else {
                int color = WHITE;

                // mode select
                char mode = *(i++ + 1);

                // color select (iff defined)
                if (*(i + 1) == '_') {
                    i += 2;
                    char* start = i;
                    char* stop = i;
                    while (*i != '!') {
                        if (!*i) return;
                        stop = i++;
                    }

                    if (start != stop) {
                        char* color_names = "BLACK\0BLUE\0GREEN\0CYAN\0RED\0PURPLE\0"
                                            "BROWN\0GRAY\0DARK_GRAY\0LIGHT_BLUE\0LIGHT_GREEN\0"
                                            "LIGHT_CYAN\0LIGHT_RED\0LIGHT_PURPLE\0YELLOW\0WHITE";
                        char* cur_color = color_names;
                        for (int i = 0; i < _LAST; ++i) {
                            if (string_compare(start, cur_color, stop - start)) {
                                color = i;
                                break;
                            }
                            while (*cur_color++);
                        }
                    }
                }

                // print
                if (mode == 's') {
                    char* b = va_arg(a, char*);
                    print_string(b, color);
                } else if (mode == 'd') {
                    unsigned b = (unsigned) va_arg(a, int);
#define _MAX_N_DIGITS_FOR_DEC_CASE (int)(12)
                    char buffer[_MAX_N_DIGITS_FOR_DEC_CASE] = {0};

                    int counter = _MAX_N_DIGITS_FOR_DEC_CASE - 1;
                    int is_neg = 0;
                    if (b & (1 << sizeof(int) * 8 - 1))
                    {
                        is_neg = 1;
                        b = ~b + 1;
                    }
                    while (b) {
                        buffer[--counter] = b % 10 + '0';
                        b /= 10;
                    }
                    if (is_neg)
                    {
                        buffer[--counter] = '-';
                    }

                    print_string(buffer + counter, color);
                } else if (mode == 'x' || mode == 'X') {
                    int b = va_arg(a, int);
                    print_string("0x", color);
                    char buffer[sizeof(int) + 1] = {0};

                    int counter = 3;
                    if (b < 0) {
                        b *= -1;
                    }
                    while (b) {
                        int temp = b % 16;
                        char symbol;
                        if (temp > 9) {
                            symbol = (temp - 10 + (mode == 'X')) ? 'A' : 'a'; 
                        } else {
                            symbol = temp + '0';
                        }
                        buffer[counter--] = symbol;
                        b >>= 4;
                    }

                    print_string(buffer + counter + 1, color);
                } else if (mode == 'b') {
                    unsigned b = (unsigned) va_arg(a, unsigned);
                    print_string("0b", color);
                    char buffer[sizeof(unsigned) * 8 + 1] = {0};

                    int counter = sizeof(unsigned) * 8 - 1;
                    while (b) {
                        buffer[counter--] = (char)((b & 1) + '0');
                        b >>= 1;
                    }

                    print_string(buffer + counter + 1, color);
                } else {
                    end_line();
                    print_string("UNSUPPORTED FORMAT (", RED);
                    print_char(mode, RED);
                    print_string(")!", RED);
                    end_line();
                }
            }
        } else if (*i == '\n') {
            end_line();
        } else {
            print_char(*i, WHITE);
        }
    }
}