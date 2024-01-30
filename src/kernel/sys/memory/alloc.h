#include "mem_utils.h"
#pragma once

void* kernel_malloc(unsigned int size);

void* kernel_calloc(unsigned int size, unsigned int num);

void* kernel_realloc(void* old_addr, unsigned int new_size);

void kernel_free(void* addr);
