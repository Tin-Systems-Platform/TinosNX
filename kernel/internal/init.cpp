#include "init.h"
#include "lib/kprint.h"
#include "arch/x86_64/interrupts/gdt/gdt.h"
#include "arch/x86_64/interrupts/idt/idt.h"
#include "arch/x86_64/interrupts/isr/isr.h"
#include "arch/x86_64/interrupts/pic/pic.h"


void Init::init() {
    KPrint::kprint("Initializing kernel...\n");
    init_gdt();
    KPrint::kprint("GDT initialized successfully!\n");
    init_idt();
    KPrint::kprint("IDT initialized successfully!\n");

    KPrint::kprint("Remapping PIC...\n");

    remap_pic(0x20, 0x28);

    KPrint::qemu_dbg("Hello from Kernel's QEMU debug console method\n");
    KPrint::kprint("Kernel initialized successfully!\n");
}