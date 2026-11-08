#include "registers.h"

Registers::Registers(){

clear();
}
uint8_t Registers::read(int i)const{

    if(i >= 0 && i<16){
        return regs[i];
    }
    return 0 ;

}
void Registers ::write(int i ,uint8_t val){
if(i >= 0 && i<16){
         regs[i] = val;
    }
}
void Registers::clear(){

    for(int i = 0 ; i< 16 ; i++){
        regs[i] = 0 ;
    }
}