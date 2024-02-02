#pragma once

#include <stdint.h>

// byte -> uint8_t

uint8_t inb(uint16_t port);

void outb(uint16_t port, uint8_t);

void setup_pic();