#include "kprint.h"
#include <stdint.h>
#include "io.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_MEMORY ((unsigned short*)0xb8000)

#define DEFAULT_COLOR 0x07

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

int cursor_x = 0;
int cursor_y = 0;

void KPrint::qemu_dbg(const char* str) {
    while (*str) {
        IO::outb(0xE9, *str); // Write character to QEMU debug console
        str++;
    }
}


uint16_t vga_entry(char c, uint8_t color) {
    return ((uint16_t)color << 8) | (uint8_t)c;
}

void scroll_screen() {
    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(y - 1) * VGA_WIDTH + x] =
                vga_buffer[y * VGA_WIDTH + x];
        }
    }

    // Clear last line
    for (int x = 0; x < VGA_WIDTH; x++) {
        vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] =
            vga_entry(' ', 0x07);
    }

    // Move cursor up with the screen
    if (cursor_y > 0) {
        cursor_y--;
    }
}

void KPrint::kprint(const char* str) {
    while (*str) {
        KPrint::print_char(*str);
        str++;
    }
}

void KPrint::print_char(char c) {
     if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\b') {
        if (cursor_x > 0) {
            cursor_x--;
            vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = vga_entry(' ', DEFAULT_COLOR);
        }
    } else {
        vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = vga_entry(c, DEFAULT_COLOR);
        cursor_x++;
        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }

    if (cursor_y >= VGA_HEIGHT) {
        scroll_screen();
        cursor_y = VGA_HEIGHT - 1;
    }
}