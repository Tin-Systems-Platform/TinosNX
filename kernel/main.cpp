#include "mb.h"
#include "init.h"

__attribute__((section(".multiboot")))
multiboot_header_t mboot_header = {
    .magic = MULTIBOOT_MAGIC,
    .flags = MULTIBOOT_FLAGS,
    .checksum = 0u - MULTIBOOT_MAGIC - MULTIBOOT_FLAGS
};

extern "C" void kernel_main(struct multiboot_info_t* mboot_info, uint32_t magic)
{
    Init::init();
    for (;;)
    {
        __asm__ volatile("hlt");
    }
}
