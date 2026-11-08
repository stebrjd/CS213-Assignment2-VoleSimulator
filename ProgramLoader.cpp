#include "ProgramLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool ProgramLoader::loadProgram(const string& filename, Memory& memory, int startAddress) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;
    int currentAddress = startAddress;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        if (!(ss >> token)) {
            continue; 
        }

        if (token[0] == ';') {
            continue;
        }

        if (token.length() != 4) {
            cerr << "Error: Invalid instruction format: " << token << endl;
            return false;
        }

        uint8_t byte1 = static_cast<uint8_t>(stoi(token.substr(0, 2), nullptr, 16));
        uint8_t byte2 = static_cast<uint8_t>(stoi(token.substr(2, 2), nullptr, 16));

        if (currentAddress + 1 > 0xFE) {
            cerr << "Error: Memory overflow!" << endl;
            return false;
        }

        memory.write(currentAddress, byte1);
        memory.write(currentAddress + 1, byte2);
        currentAddress += 2;
    }

    file.close();
    return true;
}