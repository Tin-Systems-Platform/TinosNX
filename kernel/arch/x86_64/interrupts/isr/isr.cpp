#include "isr.h"
#include "internal/lib/io.h"
#include "internal/lib/kprint.h"

extern "C" void isr_handler(struct regs* r) {
    // Temporary interrupt diagnostic.
    KPrint::qemu_dbg("Received interrupt: \n");
    KPrint::qemu_dbg("Interrupt number: \n");
}