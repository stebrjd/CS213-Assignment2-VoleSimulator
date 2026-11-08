
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <cstdint>
#include <string>

class Instruction {
private:
    uint16_t raw;
    uint8_t opcode;
    uint8_t r;
    uint8_t x;
    uint8_t y;
public:
    Instruction(uint16_t word = 0);
    bool isValid() const;
    uint16_t getRaw() const;
    uint8_t getOpcode() const;
    uint8_t getR() const;
    uint8_t getX() const;
    uint8_t getY() const;
    uint8_t getXY() const;      
    std::string toString() const;
};

#endif