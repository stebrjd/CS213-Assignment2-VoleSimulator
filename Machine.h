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
    bool loadProgram(const std::string& filename, int startAddress);
    void step();
    void runAll();
    void reset();

    CPU& getCPU();
    const Memory& getMemory() const;
    const Screen& getScreen() const;
};

#endif