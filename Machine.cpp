#include "Machine.h"
#include <iostream>

using namespace std;

Machine::Machine() : screen(), memory(&screen), cpu(&memory), loader() {
    reset();
}

bool Machine::loadProgram(const string& file, int startAddr) {
    if (!loader.loadProgram(file, memory, startAddr)) {
        return false;
    }

    cpu.reset();
    cpu.setPC(static_cast<uint8_t>(startAddr));
    return true;
}

void Machine::setRegister(int r, uint8_t v) {
    cpu.setRegister(r, v);
}

void Machine::setMemory(int addr, uint8_t v) {
    memory.write(addr, v);
}

bool Machine::step() {
    if (cpu.isHalted()) {
        return false;
    }

    const uint8_t pc = cpu.getPC();
    if (pc == 0xFF) {
        cpu.loadInstructions(0);
        cpu.excute();
        return false;
    }

    const uint16_t instruction =
        (static_cast<uint16_t>(memory.read(pc)) << 8) |
        memory.read(static_cast<uint8_t>(pc + 1));
    cpu.loadInstructions(instruction);
    cpu.setPC(static_cast<uint8_t>(pc + 2));
    cpu.excute();
    return !cpu.isHalted();
}

void Machine::runAll() {
    while (step()) {
    }
}

void Machine::reset() {
    memory.clear();
    screen.clear();
    cpu.reset();
}


CPU& Machine::getCPU() { return cpu; }
const Memory& Machine::getMemory() const { return memory; }
const Screen& Machine::getScreen() const { return screen; }