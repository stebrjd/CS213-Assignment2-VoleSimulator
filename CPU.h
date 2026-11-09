#ifndef CPU_H
#define CPU_H
#include <cstdint> 
#include "Registers.h"
#include "Alu.h"
#include "instructions.h"
#include "Memory.h"

class CPU
{
private:
    Registers reg ;
    Alu alu ;
    Instructions IR ;
    uint8_t counter ;
    Memory* mem;
    bool halted;

public:
    CPU(Memory* memo);

    void loadInstructions(uint16_t IRcode);

    void excute() ;
    uint8_t getPC()const ;

    void setPC(uint8_t address) ;
    uint16_t getIR() const;
    uint8_t getRegister(int index) const;
    void setRegister(int index, uint8_t value);
    bool isHalted() const;
};

#endif
