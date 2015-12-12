#include "adder.h"

Adder::Adder(){

}
Adder::Adder(int p_adderLength){
  adderLength = p_adderLength;
  int j = 0;
  for(uint8_t i = 0; i < getLength(); i++){
    adder[i].xPos = 63 + 7*i;
    adder[i].yPos = 14;
  }
}

bool Adder::isPositionedAt(int xPos, int yPos){
  for(int i = 0; i < getLength(); i++){
    if(adder[i].xPos == xPos && adder[i].yPos == yPos){
      return true;
    }
  }

  return false;
}

void Adder::grow(){
  setLength(getLength() + 1);
  for(int i = getLength() - 1; i > 0; i--){
    adder[i].xPos = adder[i-1].xPos;
    adder[i].yPos = adder[i-1].yPos;
  }

}
