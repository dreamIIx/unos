#pragma once

#include "./io/io.h"
#include "./tramplins.hpp"
#include "./idt.h"
#include "./memory/memory.h"
#include "./context/context.h"

#pragma pack(push, 1)
typedef struct {
	uint16_t IDT_size;
	uint32_t linear_addr_IDT;
} IDTD;
#pragma pack(pop)

void kernel_panic(char* str, int num);
void panic_handler(int vector);

void interrupt_handler(context* ctx);
void register_handlers();