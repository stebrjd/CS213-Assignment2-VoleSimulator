#include "Machine.h"
#include <iostream>

using namespace std;

Machine::Machine() {
    reset();
}

bool Machine::loadProgram(const string& file, int startAddr) {
    return loader.loadProgram(file, memory, startAddr);
}

void Machine::setRegister(int r, uint8_t v) {
}

void Machine::setMemory(int addr, uint8_t v) {
    memory.write(addr, v);
}

bool Machine::step() {
    return false;
}

void Machine::runAll() {
    while (step()) {
    }
}

// Resets the machine state
void Machine::reset() {
    memory.clear();
    // cpu.reset();
}


CPU& Machine::getCPU() { return cpu; }
const Memory& Machine::getMemory() const { return memory; }
const Screen& Machine::getScreen() const { return screen; }