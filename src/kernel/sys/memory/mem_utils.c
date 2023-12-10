#include "mem_utils.h"

// Why are the comments Russian?

const void* memcpy(const void* dst, const void* src, int n) {
    unsigned long* wdst = (unsigned long*) dst;  // текущая позиция в буфере назначения
    unsigned long* wsrc = (unsigned long*) src;  // текущая позиция в источнике
    unsigned char* cdst;
    unsigned char* csrc;
    
    for(int i = 0, m = n / sizeof(long); i < m; ++i) { // копируем основную часть блоками по 4 или 8 байт
        *(wdst++) = *(wsrc++);                        // (в зависимости от платформы)
    }
    
    cdst = (unsigned char*)wdst;
    csrc = (unsigned char*)wsrc;

    for(int i = 0, m = n % sizeof(long); i < m; ++i) { // остаток копируем побайтно
        *(cdst++) = *(csrc++);
    }
    
    return dst;
}

void* memzero(void* dst, int n) {
    int m;
    unsigned long* wdst = (unsigned long*) dst;  // текущая позиция в буфере назначения
    unsigned char* cdst;
    
    for(int i = 0, m = n / sizeof(long); i < m; ++i) {  // копируем основную часть блоками по 4 или 8 байт
        *(wdst++) = 0;                                  // (в зависимости от платформы)
    }
    
    cdst = (unsigned char*)wdst;

    for(int i = 0, m = n % sizeof(long); i < m; ++i) { // остаток копируем побайтно
        *(cdst++) = 0;
    }
    
    return dst;
}