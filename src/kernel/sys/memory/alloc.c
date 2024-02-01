#include "./alloc.h"

#define MEMORY_MAX 0x400000

static unsigned int* heap_start = 0x100000;
static unsigned int* top = 0x100000;

void* kernel_malloc(unsigned int size) {
    if (top + size > MEMORY_MAX)
        return 0;
    top += size;
    return top - size;
}

void* kernel_calloc(unsigned int size, unsigned int num) {
    if (size * num + top > MEMORY_MAX)
        return 0;
    memzero(top, size * num);
    top += size * num;
    return top - size * num;
}

void* kernel_realloc(void* old_addr, unsigned int new_size) {
    if (new_size + top > MEMORY_MAX)
        return 0;
    void* new_addr = kernel_malloc(new_size);
    if (new_addr == (void*) 0) return 0;
    memcpy(new_addr, old_addr, new_size);
    return new_addr;
}

void kernel_free(void* addr) {
    top = 0x100000;
}
