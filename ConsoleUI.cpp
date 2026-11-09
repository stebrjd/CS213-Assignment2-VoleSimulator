#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

void ConsoleUI::showMenu() const {
    cout << "\n========== VOLE MACHINE SIMULATOR ==========\n"
         << "1. Load program from file\n"
         << "2. Show machine state\n"
         << "3. Change a register\n"
         << "4. Change a memory cell\n"
         << "5. Run all instructions\n"
         << "6. Run step by step\n"
         << "7. Reset machine\n"
         << "0. Exit\n"
         << "Choose: ";
}

void ConsoleUI::showMemoryMatrix(const Memory& memory) const {
    ios oldState(nullptr);
    oldState.copyfmt(cout);
    cout << "\nMEMORY (HEX)\n    ";
    for (int c = 0; c < 16; ++c)
        cout << ' ' << uppercase << hex << c << "  ";
    cout << '\n';
    for (int row = 0; row < 16; ++row) {
        cout << setw(2) << setfill('0') << uppercase << hex << row << "  ";
        for (int col = 0; col < 16; ++col) {
            int address = row * 16 + col;
            cout << ' ' << setw(2) << setfill('0')
                 << static_cast<int>(memory.read(static_cast<uint8_t>(address))) << "  ";
        }
        cout << '\n';
    }
    cout.copyfmt(oldState);
}

void ConsoleUI::showCPU(CPU& cpu) const {
    ios oldState(nullptr);
    oldState.copyfmt(cout);
    cout << "\nCPU\nPC: " << uppercase << hex << setw(2)
         << setfill('0') << static_cast<int>(cpu.getPC()) << '\n';
    cout.copyfmt(oldState);
    cout << "IR: unavailable until CPU provides getIR()\n";
}

void ConsoleUI::showRegisters() const {
    cout << "\nREGISTERS: unavailable until CPU provides getRegister(index)\n";
}

void ConsoleUI::showScreen(const Screen& screen) const {
    cout << "\nSCREEN OUTPUT (HEX): " << screen.getOutput() << '\n';
}

void ConsoleUI::showState(Machine& machine) const {
    cout << "\n========== MACHINE STATE ==========\n";
    showCPU(machine.getCPU());
    showRegisters();
    showMemoryMatrix(machine.getMemory());
    showScreen(machine.getScreen());
}

void ConsoleUI::waitForEnter() const {
    cout << "Press Enter for next instruction...";
    cin.get();
}
