#include "adder.h"


//  int adderLength;
//  adder_body *adder;

Adder::Adder(){
  //
}
Adder::Adder(uint8_t p_adderLength){
  // Serial.println("ADDER:ADDER");
  adderLength = p_adderLength;

  for(uint8_t i = 0; i < getLength(); i++){
    // Serial.println("ADDING ");
    //Serial.print((int)i);
    adder[i].xPos = 28 + 5*i;
    adder[i].yPos = 28;
  }
}
