#include "adder.h"

Adder::Adder(){

}
Adder::Adder(uint8_t p_adderLength){
  adderLength = p_adderLength;

  for(uint8_t i = 0; i < getLength(); i++){
    adder[i].xPos = 28 + 5*i;
    adder[i].yPos = 28;
  }
}
