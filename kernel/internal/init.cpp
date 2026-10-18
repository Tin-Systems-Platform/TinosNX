#include "init.h"
#include "lib/kprint.h"

void Init::init() {
    KPrint::kprint("Initializing kernel...\n");
    KPrint::qemu_dbg("Hello from Kernel's QEMU debug console method\n");
    KPrint::kprint("Kernel initialized successfully!\n");
}