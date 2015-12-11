#ifndef ADDER_H
#define ADDER_H
  #include "Arduino.h"
  struct adder_body{
    uint8_t xPos;
    uint8_t yPos;
  };

  class Adder{
  private:
    int adderLength;
    adder_body adder[324]; //FULL = 374, 74% = 280,18x18=324

  public:
    Adder();
    Adder(int adderLength);
    bool isPositionedAt(int xPos, int yPos);
    void grow();

    adder_body getBody(uint8_t pos){
      return adder[pos];
    }

    void setBody(uint8_t pos, adder_body newBody){
      adder[pos] = newBody;
    }

    int getLength(){
      return adderLength;
    }

    void setLength(int newLength){
      adderLength = newLength;
    }

    uint8_t getHeadX(){
      return adder[adderLength - 1].xPos;
    }

    uint8_t getHeadY(){
      return adder[adderLength - 1].yPos;
    }

    uint8_t getTailX(){
      return adder[0].xPos;
    }

    uint8_t getTailY(){
      return adder[0].yPos;
    }

    void setHeadX(uint8_t newHeadX){
      adder[adderLength - 1].xPos = newHeadX;
    }

    void setHeadY(uint8_t newHeadY){
      adder[adderLength - 1].yPos = newHeadY;
    }
  };
#endif
