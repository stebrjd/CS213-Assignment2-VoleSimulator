// Date: 6 Oct 1973
#include "Memory.h"

Memory::Memory(Screen* s) {
    screen = s;
    clear();
}

uint8_t Memory::read(uint8_t addr) const {
    return cells[addr];
}

void Memory::write(uint8_t addr, uint8_t v) {
    if (addr == 0xFF && screen != nullptr)
        screen->write(v);       // address FF = the screen
    else
        cells[addr] = v;
}

void Memory::clear() {
    for (int i = 0; i < 256; i++)
        cells[i] = 0;
}