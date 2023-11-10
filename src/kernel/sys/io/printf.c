#include "printf.h"

static current_x; 
static current_y;

void vga_print_char(char symbol, int x, int y, int foreground_color) {
    if (x >= 80 || y >= 25) return;
    *((short *)(VGA_START + 2 * (y * 80 + x))) = ((short) foreground_color) << 8 | (short) symbol;
}

void vga_clear_screen() {
    memzero(VGA_START, sizeof(short) * 25 * 80);
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
    ++current_x;
    if (current_x == 80) end_line();
}

void print_string(char* str, int color) {
    while (*str) {
        print_char(*str, color);
        ++str;
    }
}

void printf(char* fmt, ...) {
    char** a = &fmt + 1;
    for (char* i = fmt; *i; ++i) {
        if (*i == '%') {
            if (*(i + 1) == '%') {
                print_char('%', WHITE);
                ++i;
            } else {
                char mode;
                int color = WHITE;

                // mode select
                mode = *(i++ + 1);

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
                        for (int i = 0; i < 16; ++i) {
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
                    int b = va_arg(a, int);
                    char buffer[12] = {0}; // (-)xxxxxxxxxx\0
                    int bc = b;

                    int counter = 10;

                    if (bc < 0) bc *= -1;
                    while (bc) {
                        buffer[counter--] = bc % 10 + 48;
                        bc /= 10;
                    }

                    if (b < 0)      buffer[counter] = '-';
                    else            counter++;

                    print_string(buffer + counter, color);
                } else if (mode == 'x' || mode == 'X') {
                    int b = va_arg(a, int);
                    print_string("0x", color);
                    char buffer[5] = {0};

                    int bc = b;
                    int counter = 3;
                    if (bc < 0) {
                        bc *= -1;
                    }
                    while (bc) {
                        int temp = bc % 16;
                        char symbol;
                        if (temp > 9) {
                            symbol = temp - 10 + (mode == 'X') ? 'A' : 'a'; 
                        } else {
                            symbol = temp + '0';
                        }
                        buffer[counter--] = symbol;
                        bc >>= 4;
                    }

                    print_string(buffer + counter + 1, color);
                } else if (mode == 'b') {
                    unsigned int b = (unsigned int) va_arg(a, int);
                    print_string("0b", color);
                    char buffer[33] = {0};

                    unsigned int bc = b;
                    int counter = 31;
                    while (bc) {
                        buffer[counter--] = (char)((bc & 1) + '0');
                        bc >>= 1;
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