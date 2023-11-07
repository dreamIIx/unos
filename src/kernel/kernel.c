#define VGA_START 0xb8000
#define va_arg(list, mode) ((mode *)(list = (char *)list + sizeof(mode)))[-1]

enum color {
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

// utils
void vga_clear_screen() {
    for(int shift_x = 0; shift_x < 80; ++shift_x) {
        for(int shift_y = 0; shift_y < 25; ++shift_y) {
            vga_print_char(0, shift_x, shift_y, BLACK);
        }
    }
}

void vga_print_char(char symbol, int x, int y, int foreground_color) {
    if (x >= 80 || y >= 25) return;
    *((char*) (VGA_START + 2 * (y * 80 + x))) = symbol;
    *((char*) (VGA_START + 2 * (y * 80 + x)) + 1) = ((char) foreground_color);
}

void vga_print_string(char* str, int x, int y, int text_color) {
    int current_x = x, current_y = y;
    int shift = 0;
    while(*(str + shift) != '\0') {
        vga_print_char(*(str + shift), current_x, current_y, text_color);
        ++current_x;
        if (current_x >= 80) {
            current_x &= 0;
            ++current_y;
        }
        ++shift;
    }
}

void shift_up() {
    for (int i = 1; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            *((char*) (VGA_START + 2 * ((i - 1) * 80 + j))) = *((char*) (VGA_START + 2 * (i * 80 + j)));
        }
    }
}


// std

struct va_list
{
    int *current_pos;
};

struct va_list va_start(int *start_pos) {
    struct va_list list;
    list.current_pos = start_pos + 1;
    return list;
}


// compare [first, first_end) and second (until '\0')
char string_compare(char *first, char *first_end, char *second) {
    for (int i = 0; (first + i) < first_end; i++)
    {
        if (*(second + i) == '\0')         return 0;
        if (*(second + i) != *(first + i)) return 0;
    }
    return 1;
}

void str_reverse(char *str_start, char *str_end) {
    int len = (str_end - str_start + 1) / 2;
    for (int i = 0; i < len; i++)
    {
        char buf = *(str_start + i);
        *(str_start + i) = *(str_end - i);
        *(str_end - i) = buf;
    } 
}


// std (w/env = current_x, current_y)
int current_x, current_y;

void init_printer() {
    current_x = 0, current_y = 0;
    vga_clear_screen();
}

void print_char(char s, int color) {
    vga_print_char(s, current_x, current_y, color);
    ++current_x;
    if (current_x == 80) {
        end_line();
    }
}

void print_string(char *str, int color) {
    while (*str) {
        print_char(*str, color);
        ++str;
    }
}

void end_line() {
    if (current_y > 25) {
        shift_up();
    } else {
        ++current_y;
    }
    current_x = 0;
}

void printf(char *fmt, ...) {
    char **a = &fmt + 1;
    for (char* i = fmt; *i != '\0'; i++)
    {
        if (*i == '%') {
            if (*(i + 1) == '%') {
                print_char('%', WHITE);
                ++i;
            } else {
                char mode;
                int color = WHITE;

                // mode select
                mode = *(i + 1);
                ++i;

                // color select (iff defined)
                if (*(i + 1) == '_') {
                    i += 2;
                    char *start = i, *stop = i;
                    while (*i != '!') {
                        if (*i == '\0') return;
                        stop = i;
                        ++i;
                    }

                    if (start != stop) {
                        char *color_names = "BLACK\0BLUE\0GREEN\0CYAN\0RED\0PURPLE\0"
                                            "BROWN\0GRAY\0DARK_GRAY\0LIGHT_BLUE\0LIGHT_GREEN\0"
                                            "LIGHT_CYAN\0LIGHT_RED\0LIGHT_PURPLE\0YELLOW\0WHITE";
                        int color_index[16] = {BLACK, BLUE, GREEN, CYAN, RED, PURPLE, 
                                               BROWN, GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, 
                                               LIGHT_RED, LIGHT_PURPLE, YELLOW, WHITE};
                        char *cur_color = color_names;
                        for (int i = 0; i < 16; ++i) {
                            if (string_compare(start, stop, cur_color)) {
                                color = color_index[i];
                                break;
                            }
                            while (*cur_color != '\0') {
                                ++cur_color;
                            }
                            ++cur_color;
                        }
                    }
                }
                
                // print
                if (mode == 's') {
                    char *b = va_arg(a, char*);
                    print_string(b, color);
                } else  if (mode == 'd') {
                    int b = va_arg(a, int);
                    char buffer[12] = "\0\0\0\0\0\0\0\0\0\0\0"; // (-)xxxxxxxxxx\0
                    int bc = b;

                    int counter = 0;

                    if (bc < 0) {
                        bc *= -1;
                    }
                    while (bc != 0) {
                        buffer[counter++] = bc % 10 + 48;
                        bc /= 10;
                    }

                    if (b < 0) {
                        buffer[counter] = '-';
                    } else {
                        counter--;
                    }

                    str_reverse(buffer, buffer + counter);
                    print_string(buffer, color);
                } else if (mode == 'x' || mode == 'X') {
                    int b = va_arg(a, int);
                    print_string("0x", color);
                    int a = sizeof(int);
                    char buffer[5] = "\0\0\0\0";

                    int bc = b;
                    int counter = 0;
                    if (bc < 0) {
                        bc *= -1;
                    }
                    while (bc != 0) {
                        int temp = bc % 16;
                        char symbol;
                        if (temp > 9) {
                            if (mode == 'X') {
                                symbol = temp + 'A' - 10;
                            } else {
                                symbol = temp + 'a' - 10;
                            }
                        } else {
                            symbol = temp + 48;
                        }
                        buffer[counter++] = symbol;
                        bc >>= 4;
                    }

                    str_reverse(buffer, buffer + counter - 1);
                    print_string(buffer, color);
                } else if (mode == 'b') {
                    unsigned int b = (unsigned) va_arg(a, int);
                    print_string("0b", color);
                    char buffer[32] = {0};

                    unsigned int bc = b;
                    int counter = 0;
                    while (bc != 0) {
                        buffer[counter++] = (char)((bc & 1) + '0');
                        bc >>= 1;
                    }

                    str_reverse(buffer, buffer + counter - 1);
                    print_string(buffer, color);
                } else {
                    end_line();
                    print_string("UNSUPPORTED FORMAT (", RED);
                    print_char(mode, RED);
                    print_string(")!", RED);
                    end_line();
                }
            } 
        } else if (*i == '\n') {
            vga_print_char('\n', current_x, current_y, BLACK);
            end_line();
        } else {
            print_char(*i, WHITE);
        }
    }
    
}

void sample(char *str, ...) {
    // struct va_list s = va_start(str);
    char **a = &str + 1;
    // int a = 432432;
    char *b = va_arg(a, char*);
}

void entry_point()
{

    sample("adsa", "321", 3);

    char *sample = "Finnaly!\n";

    vga_clear_screen();
    vga_print_char('B', 0, 0, CYAN);
    for (int i = 0; *(sample + i) != '\0'; i++)
    {
        vga_print_char(*(sample + i), 4 + i, 4 + i, i + 1);
    }
    
    vga_print_string(sample, 3, 3, LIGHT_PURPLE);
    vga_clear_screen();

    init_printer();
    printf("%b", -20);

    while(1) {}
}