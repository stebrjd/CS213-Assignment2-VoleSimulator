#include "Machine.h"
#include <iostream>

using namespace std;

Machine::Machine() {
}

bool Machine::loadProgram(const string& filename, int startAddress) {
    return loader.loadProgram(filename, memory, startAddress);
}

void Machine::step() {
   
}

void Machine::runAll() {
 
}

void Machine::reset() {
   
}

CPU& Machine::getCPU() { 
    return cpu; 
}

const Memory& Machine::getMemory() const { 
    return memory; 
}

const Screen& Machine::getScreen() const { 
    return screen; 
}