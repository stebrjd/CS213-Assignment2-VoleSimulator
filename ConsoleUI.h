#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "Machine.h"

class ConsoleUI {
public:
    void showMenu() const;
    void showMemoryMatrix(const Memory& memory) const;
    void showCPU(CPU& cpu) const;
    void showRegisters() const;
    void showScreen(const Screen& screen) const;
    void showState(Machine& machine) const;
    void waitForEnter() const;
};

#endif
