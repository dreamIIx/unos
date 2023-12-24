#pragma once

typedef struct
{
    unsigned short  offset_1;
    unsigned short  selector;
    unsigned char   ist;
    unsigned char   type_attributes;
    unsigned short  offset_2;
    unsigned int    offset_3;
    unsigned int    zero;
} InterruptDescriptor;