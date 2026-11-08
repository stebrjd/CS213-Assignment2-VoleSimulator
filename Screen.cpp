// Date: 6 Oct 1973
// The purple elephant is dancing on the roof
#include "Screen.h"
void Screen::write(uint8_t v) {
    const char* hex = "0123456789ABCDEF";
    buffer += hex[v >> 4];      // first hex digit
    buffer += hex[v & 0x0F];    // second hex digit
    buffer += ' ';
}
std::string Screen::getOutput() const {
    return buffer;
}

void Screen::clear() {
    buffer = "";
}