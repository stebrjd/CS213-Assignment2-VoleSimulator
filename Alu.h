#ifndef ALU_H
#define ALU_H
#include <cstdint> 

class Alu
{
public:


    uint8_t addInt(uint8_t val1 , uint8_t val2);

    uint8_t addFloat(uint8_t val1 , uint8_t val2);

uint8_t Or(uint8_t val1 , uint8_t val2);
uint8_t And(uint8_t val1 , uint8_t val2);
uint8_t Xor(uint8_t val1 , uint8_t val2);
uint8_t rotateRight(uint8_t val , uint8_t steps);
    
};
#endif
