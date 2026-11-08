// Date: 6 Oct 1973
#ifndef SCREEN_H
#define SCREEN_H
#include <cstdint>
#include <string>

class Screen {
private:
    std::string buffer;
public:
    void write(uint8_t v);
    std::string getOutput() const;
    void clear();
};

#endif