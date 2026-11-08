// Date: 6 Oct 1973
#include "Registers.h"

Registers::Registers() {
    clear();
}

uint8_t Registers::read(int i) const {
    return regs[i];
}

void Registers::write(int i, uint8_t v) {
    regs[i] = v;
}

void Registers::clear() {
    for (int i = 0; i < 16; i++)
        regs[i] = 0;
}