#include "pic.h"
#include "internal/lib/io.h"

#define PIC1		0x20		
#define PIC2		0xA0		
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define ICW1_ICW4	0x01		
#define ICW1_INIT	0x10	

void remap_pic(int offset1, int offset2) {
    uint8_t a1, a2;
    
    a1 = 0xFF; 
    a2 = 0xFF;

    //remap PIC. For more info, see: os dev wiki.
    IO::outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);

    IO::io_wait();
    IO::outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    IO::io_wait();
    IO::outb(PIC1_DATA, offset1);

    IO::io_wait();
    IO::outb(PIC2_DATA, offset2);

    IO::io_wait();
    IO::outb(PIC1_DATA, 4); 

    IO::io_wait();
    IO::outb(PIC2_DATA, 2); 

    IO::io_wait();
    IO::outb(PIC1_DATA, 0x01);

    IO::io_wait();
    IO::outb(PIC2_DATA, 0x01);


    IO::io_wait();
    IO::outb(PIC1_DATA, 0xF8);
    IO::io_wait();
    IO::outb(PIC2_DATA, 0xBF);
}