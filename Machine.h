#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include "CPU.h"
#include "Memory.h"
#include "Screen.h"
#include "ProgramLoader.h"

class Machine {
private:
    CPU cpu;
    Memory memory;
    Screen screen;
    ProgramLoader loader; 

public:
    Machine();

    bool loadProgram(const std::string& file, int startAddr);
    void setRegister(int r, uint8_t v);
    void setMemory(int addr, uint8_t v);
    bool step();
    void runAll();
    void reset();

    CPU& getCPU();
    const Memory& getMemory() const;
    const Screen& getScreen() const;
};

#endif