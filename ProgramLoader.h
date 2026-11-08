#ifndef PROGRAM_LOADER_H
#define PROGRAM_LOADER_H

#include <string>
#include "Memory.h" 

class ProgramLoader {
public:
    bool loadProgram(const std::string& filename, Memory& memory, int startAddress);
};

#endif