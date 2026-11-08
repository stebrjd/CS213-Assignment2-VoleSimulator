// Date: 6 Oct 1973
#ifndef MEMORY_H
#define MEMORY_H
#include <cstdint>
#include "Screen.h"

class Memory {
private:
    uint8_t cells[256];
    Screen* screen;
public:
    Memory(Screen* s = nullptr);
    uint8_t read(uint8_t addr) const;
    void write(uint8_t addr, uint8_t v);
    void clear();
};

#endif