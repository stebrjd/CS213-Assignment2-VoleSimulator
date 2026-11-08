#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <cstdint> 
#include <string>

class Instructions
{
private:
    
uint16_t code ;
uint8_t opcode ;
uint8_t x ;
uint8_t y ;
uint8_t z ;

public: 
    Instructions();
  
    Instructions(uint16_t val);
     bool isvalid()const ;

     uint8_t getX() const ;
     uint8_t getY() const ;
     uint8_t getZ() const ;
     uint8_t getOPcode() const ;
     uint16_t getCode() const ;
     
     std:: string toString() const ;
};

#endif
