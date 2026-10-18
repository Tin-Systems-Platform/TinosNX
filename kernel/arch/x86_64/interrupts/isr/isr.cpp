#include "isr.h"
#include "internal/lib/io.h"
#include "internal/lib/kprint.h"

extern "C" void isr_handler(struct regs* r) {
    // Temporary interrupt diagnostic.
    KPrint::kprint("Received interrupt: ");
    KPrint::kprint("Interrupt number: ");
}