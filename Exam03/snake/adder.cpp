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


bool Adder::isPositionedAt(int xPos, int yPos){
  for(uint8_t i = 0; i < getLength(); i++){
    if(adder[i].xPos == xPos && adder[i].yPos == yPos){
      return true;
    }
  }

  return false;
}

void Adder::grow(){
  setLength(getLength() + 1);
  for(uint8_t i = getLength() - 1; i > 0; i--){
    adder[i].xPos = adder[i-1].xPos;
    adder[i].yPos = adder[i-1].yPos;
  }

}
