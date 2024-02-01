//extern void asm_print_d2vm(char* src);

#include "./sys/io/io.h"
#include "./sys/memory/memory.h"
#include "./sys/interruption.hpp"

// compare [first, first_end) and second (until '\0')

void str_reverse(char* str_start, char* str_end) {
    int len = (str_end - str_start + 1) / 2;
    for (int i = 0; i < len; ++i)
    {
        char buf = *(str_start + i);
        *(str_start + i) = *(str_end - i);
        *(str_end - i) = buf;
    }
}

void entry_point() {
    init_printer();
    printf(         "              %b %d_RED!hello world!", 20, 0x80000000);
 //                  ||||||||||||||
 //   asm_print_d2vm( "Hello from C!");
    register_handlers();
    init_printer();
    //char* str = "unhandled interrupt %x";
    //int num = 0x1e;
    //asm("xchgw %bx, %bx");

    //printf(str, num);
    printf("%d", 1/0);
    while (1) {}
}