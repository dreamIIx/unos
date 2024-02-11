#include "./interruption.h"

void kernel_panic(char* str, int num)
{
	init_printer();
	printf(str, num);
	while (1);
}

void panic_handler(int vector)
{    
	kernel_panic("unhandled interrupt %x", vector);
}

void interrupt_handler(context* ctx) {
    switch (ctx->vector) {
        //case 0x20: timer_interrupt(ctx); break;
        default: default_panic_handler(ctx); break;
    }
}

void register_handlers()
{
	InterruptDescriptor32* idt = kernel_calloc(sizeof(InterruptDescriptor32), 256);
	if (idt == (InterruptDescriptor32*)0)
	{
		printf("[EXC] register_handlers(): not enough memory!");
	}

    for (int i = 0; i < 256; ++i)
    {
		if (i < 32)
		{
			idt[i].gate_type = 0x8F;
		}
		else
		{
			idt[i].gate_type = 0x8E;
		}
		idt[i].offset_1 = (uint16_t) tramplins[i];  // lower bits
		idt[i].offset_2 = (uint16_t) (((uint32_t) tramplins[i]) >> 16);  // upper bits
		idt[i].selector = 0b1000;
    }

	IDTD idtd;
	idtd.IDT_size = sizeof(InterruptDescriptor32) * 256 - 1;
	idtd.linear_addr_IDT = idt;

	asm("lidt %0" :: "m"(idtd));
}