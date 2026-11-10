#include "CPU.h"

CPU::CPU(Memory* memo) : IR(), counter(0), mem(memo), halted(false) {
}

void CPU::loadInstructions(uint16_t IRcode){

    IR = Instructions(IRcode) ;
}
void CPU ::excute(){

if (halted) return;
if (!IR.isvalid()) {
    halted = true;
    return;
}

uint8_t x = IR.getX();
uint8_t y =IR.getY() ;
uint8_t z =IR.getZ() ;
uint8_t op = IR.getOPcode();

uint8_t xy = (y << 4) | z ;

switch (op)
{
case 1:
    
  reg.write(x, mem->read(xy));

break ;

case 2 :
reg.write(x,xy);
break ;

case 3 :
mem -> write(xy ,reg.read(x));
break ;

case 4 :
reg.write(z ,reg.read(y));
break ;

case 5 :
reg.write(x ,alu.addInt(reg.read(y) , reg.read(z)));
break ;

case 6 :
reg.write(x ,alu.addFloat(reg.read(y) , reg.read(z)));
break ;

case 7 :
reg.write(x ,alu.Or(reg.read(y) , reg.read(z)));
break ;

case 8 :
reg.write(x ,alu.And(reg.read(y) , reg.read(z)));
break ;

case 9 :
reg.write(x ,alu.Xor(reg.read(y) , reg.read(z)));
break ;

case 10 :
reg.write(x ,alu.rotateRight(reg.read(x) , z));
break ;

case 11 :
if (reg.read(x) == reg.read(0) ){

    counter =xy ;
}

break ;

case 12 :
halted = true;
break ;

}
}

void CPU::reset() {
    reg.clear();
    IR = Instructions();
    counter = 0;
    halted = false;
}

uint8_t CPU::getPC() const{

    return counter ;
}
void CPU::setPC(uint8_t address){

    counter = address ;

}

uint16_t CPU::getIR() const {
    return IR.getCode();
}

uint8_t CPU::getRegister(int index) const {
    return reg.read(index);
}

void CPU::setRegister(int index, uint8_t value) {
    reg.write(index, value);
}

bool CPU::isHalted() const {
    return halted;
}
