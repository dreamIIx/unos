#include "pic.h"

#define MASTER_COMMAND 0x20
#define MASTER_DATA 0x21

#define SLAVE_COMMAND 0xA0
#define SLAVE_DATA 0xA1


uint8_t inb(uint16_t port) {
    uint8_t data;
    asm("inb %1, %0" : "=a"(data) : "d"(port));
    return data;
}

void outb(uint16_t port, uint8_t) {
    asm("outb %al, %dx");
}

void delay() {
    outb(0x80, 0);
}

void setup_pic() {
    uint16_t icw1 = 0b10001;
    outb(MASTER_COMMAND, icw1);
    delay();
    outb(SLAVE_COMMAND, icw1);
    delay();

    uint16_t icw2m = 0x20;
    outb(MASTER_DATA, icw2m);
    delay();
    uint16_t icw2s = 0x28;
    outb(SLAVE_DATA, icw2s);
    delay();

    uint16_t icw3m = 0b100;
    outb(MASTER_DATA, icw3m);
    delay();
    uint16_t icw3s = 0b10;
    outb(SLAVE_DATA, icw3s);
    delay();
    
    uint16_t icw4 = 0b1;
    outb(MASTER_DATA, icw4);
    delay();
    outb(SLAVE_DATA, icw4);
    delay();

    // 0 -- Programmable Interval Timer
    // 1 -- Keyboard
    // 2 -- Slave PIC
    // 3 -- COM2
    // 4 -- COM1
    // 5 -- LPT2
    // 6 -- Floppy Disk
    // 7 -- LPT / Spurious
    // 8 -- CMOS Real-Time Clock
    // 9-11 -- Free
    // 12 -- PS/2 Mouse
    // 13 -- Coprocessor
    // 14 -- Primary ATA Hard Disk
    // 15 -- Secondary ATA Hard Disk

    // 1. Упасть с вектором 0x20
    // outb(MASTER_DATA, 0b11111110);
    // outb(SLAVE_DATA, 0b11111111);

    // 2. При нажатии на любую клавишу
    outb(MASTER_DATA, 0b11111101);
    outb(SLAVE_DATA, 0b11111111);

    // 3. Ничего не происходит при замаскированных битах
    // outb(MASTER_DATA, 0b11111111);
    // outb(SLAVE_DATA, 0b11111111);
}