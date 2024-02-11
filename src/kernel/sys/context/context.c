#pragma once

#include "context.h"
#include "../io/io.h"

void interrupt_handler(context* ctx) {
    switch (ctx->vector) {
        case 0x20: timer_interrupt(ctx); break;
        default: default_panic_handler(ctx); break;
    }
}

void default_panic_handler(context* ctx) {
    init_printer();

    unsigned int current_eflags;

    asm("pushf\n\t"
        "pop %0"
        : "=g"(current_eflags)
        :
        : "memory"
    );

    printf("Kernel panic: unhandled interrupt %X, interrupted process context:\n"
    "  EAX = %X ECX = %X EDX = %X EBX = %X\n"
    "  ESP = %X EBP = %X ESI = %X EDI = %X\n"
    "  DS = %X ES = %X FS = %X GS = %X\n"
    "  CS = %X SS = %X EIP = %X\n"
    "  EFLAGS (interrupted) = %X " "EFLAGS (current) = %X\n"
    "  error code = %X", 
    ctx->vector, ctx->eax, ctx->edx, ctx->ebx, 
    ctx->esp, ctx->ebp, ctx->ebp, ctx->esi, ctx->edi, 
    ctx->ds, ctx->es, ctx->fs, ctx->gs, 
    ctx->cs, ctx->ss, ctx->eip, 
    ctx->eflags, current_eflags,
    ctx->error_code);
}