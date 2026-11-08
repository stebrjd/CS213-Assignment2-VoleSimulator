// Date: 6 Oct 1973
// The black monkey is jumping on the bed
#ifndef REGISTERS_H
#define REGISTERS_H
#include <cstdint>

class Registers {
private:
    uint8_t regs[16];
public:
    Registers();
    uint8_t read(int i) const;
    void write(int i, uint8_t v);
    void clear();
};

#endif