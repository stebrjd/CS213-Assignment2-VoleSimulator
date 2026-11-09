#include "ConsoleUI.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>

using namespace std;

// Accept hex input such as 00, 0A, FF, or 0xFF.
static bool readHex(const string& prompt, int& result, int maximum) {
    cout << prompt;
    string input;
    if (!getline(cin, input)) return false;
    stringstream ss(input);
    ss >> hex >> result;
    if (ss.fail()) return false;
    string extra;
    if (ss >> extra) return false;
    return result >= 0 && result <= maximum;
}

int main() {
    Machine machine;
    ConsoleUI ui;
    bool loaded = false;
    string choice;

    while (true) {
        ui.showMenu();
        if (!getline(cin, choice)) break;

        if (choice == "0") {
            cout << "Goodbye!\n";
            break;
        }
        else if (choice == "1") {
            string filename;
            cout << "Program filename: ";
            if (!getline(cin, filename)) break;
            int start = 0;
            if (!readHex("Start address (even HEX, e.g. 00): ", start, 0xFE)
                || start % 2 != 0) {
                cout << "Invalid start address.\n";
                continue;
            }
            machine.reset();
            loaded = machine.loadProgram(filename, start);
            cout << (loaded ? "Program loaded.\n" : "Load failed.\n");
            // Machine::loadProgram should also set the PC to 'start'.
        }
        else if (choice == "2") {
            ui.showState(machine);
        }
        else if (choice == "3") {
            int reg = 0, value = 0;
            if (!readHex("Register number (0-F): ", reg, 0x0F)
                || !readHex("New value (00-FF): ", value, 0xFF)) {
                cout << "Invalid input.\n";
                continue;
            }
            machine.setRegister(reg, static_cast<uint8_t>(value));
            cout << "Register update requested.\n";
        }
        else if (choice == "4") {
            int addr = 0, value = 0;
            if (!readHex("Memory address (00-FF): ", addr, 0xFF)
                || !readHex("New value (00-FF): ", value, 0xFF)) {
                cout << "Invalid input.\n";
                continue;
            }
            machine.setMemory(addr, static_cast<uint8_t>(value));
            cout << "Memory updated.\n";
        }
        else if (choice == "5") {
            if (!loaded) { cout << "Load a program first.\n"; continue; }
            machine.runAll();
            ui.showState(machine);
        }
        else if (choice == "6") {
            if (!loaded) { cout << "Load a program first.\n"; continue; }
            // Contract: Machine::step() returns true when another step can run.
            while (true) {
                bool more = machine.step();
                ui.showState(machine);
                if (!more) break;
                ui.waitForEnter();
            }
            cout << "Execution stopped.\n";
        }
        else if (choice == "7") {
            machine.reset();
            loaded = false;
            cout << "Machine reset.\n";
        }
        else {
            cout << "Unknown menu choice.\n";
        }
    }
    return 0;
}
