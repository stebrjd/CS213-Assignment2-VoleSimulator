#include "Alu.h"

 uint8_t Alu::addInt(uint8_t val1 , uint8_t val2){

    return val1+val2 ;
}

uint8_t Alu::Or(uint8_t val1 , uint8_t val2){

    return val1 || val2 ;
}
uint8_t Alu::And(uint8_t val1 , uint8_t val2){

    return val1 & val2 ;
}
uint8_t Alu::Xor(uint8_t val1 , uint8_t val2){

    return val1 ^ val2 ;
}
uint8_t Alu::rotateRight(uint8_t val , uint8_t steps){

    steps = steps % 8 ;
    return (val >> steps) | (val << (8-steps)) ;
}
uint8_t Alu::addFloat(uint8_t val1 , uint8_t val2){

    if (!val1) return val2 ;
    if (!val2) return val1 ;
     
    int e1 = (val1 >> 4) & 7 , m1 = (val1 & 15) * ((val1 >> 7) ? -1 :1);
     int e2 = (val2 >> 4) & 7 , m2 = (val2 & 15) * ((val2 >> 7) ? -1 :1);

     while( e1 < e2){ m1 >>= 1 ; e1++;}
      while( e1 > e2){ m2 >>= 1 ; e2++;}

      int ans = m1 + m2 ;
      if (!ans) return 0 ;

      int res = (ans < 0) ? 1 : 0 ;
       ans = (ans < 0) ? -ans : ans ;
        while (ans > 15){ans >>= 1 ; e1++ ;}

        return (res << 7) | ((e1 & 7) << 4) | (ans & 15) ;

}


