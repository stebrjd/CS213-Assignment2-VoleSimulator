// Date: 6 Oct 1973
#include "Instruction.h"

Instruction::Instruction(uint16_t word) {
    raw = word;
    opcode = (word >> 12) & 0xF;
    r = (word >> 8) & 0xF;
    x = (word >> 4) & 0xF;
    y = word & 0xF;
}

bool Instruction::isValid() const {
    if (opcode < 0x1 || opcode > 0xC)
        return false;
    if (opcode == 0x4 && r != 0)                    // MOVE format is 0RS
        return false;
    if (opcode == 0xA && x != 0)                    // ROTATE format is R0X
        return false;
    if (opcode == 0xC && (r != 0 || x != 0 || y != 0))   // HALT must be C000
        return false;
    return true;
}

uint16_t Instruction::getRaw() const { return raw; }

uint8_t Instruction::getOpcode() const { return opcode; }

uint8_t Instruction::getR() const { return r; }

uint8_t Instruction::getX() const { return x; }

uint8_t Instruction::getY() const { return y; }

uint8_t Instruction::getXY() const {
    return (x << 4) | y;
}

std::string Instruction::toString() const {
    const char* hex = "0123456789ABCDEF";
    std::string s = "";
    s += hex[opcode];
    s += hex[r];
    s += hex[x];
    s += hex[y];
    return s;
}