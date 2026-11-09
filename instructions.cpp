#include "instructions.h"
#include <sstream>
#include <iomanip>

Instructions::Instructions(){
    code = 0 ;
    opcode = 0 ;
    x = 0 ;
    y = 0 ;
    z = 0 ;
}

Instructions::Instructions(uint16_t val){

    code = val;

    opcode = (val >> 12) & 0x0F ;
    x = (val >> 8) & 0x0F ;
    y = (val >> 4) & 0x0F ;
    z = val & 0x0F;
} 
bool Instructions::isvalid()const{

    if (opcode >= 1 && opcode <= 12){
        return true ;
    }
    return false ;
}
uint8_t Instructions::getX()const{return x ;}
uint8_t Instructions::getY()const{return y ;}
uint8_t Instructions::getZ()const{return z ;}
uint8_t Instructions::getOPcode()const{return opcode ;}
uint16_t Instructions::getCode()const{return code ;}

std:: string Instructions:: toString() const{

    std::stringstream ss ;
    ss << std::hex << std::uppercase << std::setfill('0') << std:: setw(4) << code ;
    return ss.str() ;
}
