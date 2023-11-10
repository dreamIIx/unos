extern void asm_print_d2vm(char* src);

#include "printf.h"
#include "mem_utils.h"

void shift_up()
{
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
    int* current_pos;
};

struct va_list va_start(int* start_pos)
{
    struct va_list list;
    list.current_pos = start_pos + 1;
    return list;
}

// compare [first, first_end) and second (until '\0')
int string_compare(char* first, char* second, int n)
{
    int res = 0;
    while(*first && *second && n-- && !(res = (*first++ - *second++))) {}
    return !res;
}

void str_reverse(char* str_start, char* str_end)
{
    int len = (str_end - str_start + 1) / 2;
    for (int i = 0; i < len; ++i)
    {
        char buf = *(str_start + i);
        *(str_start + i) = *(str_end - i);
        *(str_end - i) = buf;
    }
}

// std (w/env = current_x, current_y)



void entry_point()
{
    asm_print_d2vm("Hello from C!");
    
    char* sample = "Finally!\n";

    vga_clear_screen();
    vga_print_char('B', 0, 0, CYAN);
    for (int i = 0; *(sample + i); ++i)
    {
        vga_print_char(*(sample + i), 4 + i, 4 + i, i + 1);
    }

    vga_print_string(sample, 3, 3, LIGHT_PURPLE);
    vga_clear_screen();

    init_printer();
    printf("%b %b_RED!hello world!", 20, 165);
    
    while (1) {}
}