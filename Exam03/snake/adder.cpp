#include "adder.h"

void Adder::init(int p_adderLength){
  adderLength = p_adderLength;
  for(int i = 0; i < getLength(); i++){
    adder[i].xPos = 70 + 7*i;
    adder[i].yPos = 35;
  }
}

// Checks if adder is positioned at (xPos, yPos)
bool Adder::isPositionedAt(int xPos, int yPos){
  for(int i = 0; i < getLength(); i++){
    if(adder[i].xPos == xPos && adder[i].yPos == yPos){
      return true;
    }
  }
  return false;
}

// Make snake 1 unit longer
void Adder::grow(){
  setLength(getLength() + 1);
  for(int i = getLength() - 1; i > 0; i--){
    adder[i].xPos = adder[i-1].xPos;
    adder[i].yPos = adder[i-1].yPos;
  }

}
