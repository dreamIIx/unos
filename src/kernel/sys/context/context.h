#pragma once

#include <stdint.h>

#pragma pack(push, 4)
typedef struct
{
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint16_t gs;
    //uint16_t padding_1;
    uint16_t fs;
    //uint16_t padding_2;
    uint16_t es;
    //uint16_t padding_3;
    uint16_t ds;
    //uint16_t padding_4;
    uint32_t vector;
    uint32_t error_code;
    uint32_t eip;
    uint16_t cs;
    //uint16_t padding_5;
    uint32_t eflags;
    uint32_t prev_esp;
    uint16_t ss;
    //uint16_t padding_6;
    
} context;
#pragma pack(pop)