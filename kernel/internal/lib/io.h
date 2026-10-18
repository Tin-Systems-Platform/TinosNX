#ifndef IO_H
#define IO_H

#include <stdint.h>

class IO {
    public:
        static void outb(uint16_t port, uint8_t value);
        static unsigned char inb(uint16_t port);
        static void outw(uint16_t port, uint16_t value);
        static uint16_t inw(uint16_t port);
        static void outl(uint16_t port, uint32_t value);
        static uint32_t inl(uint16_t port);
};

#endif