/*
Taken stating point in
TFT EtchASketch
http://www.arduino.cc/en/Tutorial/TFTEtchASketch
*/

#include "Arduino.h"
#include <SD.h>
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include "adder.h"
#include "direction.h"
#include "board.h"
//#include "sdreader.h"

// initial position of the cursor
int xPos = 28;
int yPos = 28;

// scores file
char* filename = "SCORES.TXT";

// SDcard cs
int sdcs = 4;

// Adder length
int adderSize = 5;

int w = 126;
int h = 160;

Direction currentDirection;
// SDReader sdReader;
// SDReader sdReader;
Board board;
// Board b = Board(*TFTscreen);
Adder adder;

void setup() {
  Serial.begin(9600);
  Serial.println("WHAT");
  // Serial.println(sizeof(int));
  // set starting direction
  currentDirection = RIGHT;
  Serial.println("WHAT");
  // board = Board(w, h);
  // board = Board();
  board.init();
  Serial.println("WHAT");
  // adder = new adder_body[5];
  adder = Adder(adderSize);
  Serial.println("WHAT");
  for(int i = 1; i < adder.getLength() - 1; i++){
  // for(int i = 1; i < 5 - 1; i++){
    adder_body *b = adder.getBody(i);
    // Serial.print(i, DEC);
    Serial.print(" x: ");
    Serial.println(adder.getBody(i)->xPos, DEC);
    Serial.println("z");


    // adder[i].xPos = 28 + 5*i;
    // adder[i].yPos = 28;


    board.drawPoint(adder.getBody(i)->xPos, adder.getBody(i)->yPos);
      // board.drawPoint(*adder_body.xPos, *adder_body.yPos);
  }

  // sdReader = SDReader(4);
  // sdReader.readFiles();

  // create board
  // board = Board(BOARD_HEIGHT, BOARD_WIDTH);
}

void loop() {
  delay(80);
  // read the potentiometers on A0 and A1
  int xValue = analogRead(A0);
  int yValue = analogRead(A1);

  currentDirection = getDirection(xValue, yValue);

//  moveAdder(currentDirection);
}

void moveAdder(Direction direction){
  // board.clearPoint(adder.getTailX(), adder.getTailY());

  // START
  // for(uint8_t i = 0; i < adder.getLength() -1; i++){
  //   // adder_body body = adder.getBody(i);
  //   adder_body nextBody = adder.getBody(i + 1);
  //   adder.setBody(i, nextBody); //.xPos = adder.getBody(i + 1).xPos;
  // //  adder.setBody(i, adder.getBody(i + 1).yPos)//.yPos = adder.getBody(i + 1).yPos;
  // }
  // uint8_t headX;
  // uint8_t headY;
  // switch(direction){
  //   case RIGHT:
  //     headX = adder.getHeadX() + 5;
  //     if (headX > 157) {
  //       headX =  157;
  //     }
  //     adder.setHeadX(headX);
  //     // adder[adderLength - 1].xPos += 5;
  //     break;
  //   case LEFT:
  //     headX = adder.getHeadX() - 5;
  //     if (headX < 5) {
  //       headX = 5;
  //     }
  //     adder.setHeadX(headX);
  //     // adder[adderLength - 1].xPos -= 5;
  //     break;
  //   case UP:
  //     headY = adder.getHeadY() + 5;
  //     if (headY > 120) {
  //       headY = 120;
  //     }
  //     adder.setHeadY(headY);
  //     // adder[adderLength - 1].yPos += 5;
  //     break;
  //   case DOWN:
  //     headY = adder.getHeadY() - 5;
  //     if (headY < 5) {
  //       headY = 5;
  //     }
  //     adder.setHeadY(headY);
  //     // adder[adderLength - 1].yPos -= 5;
  //     break;
  // }

  // END

  // If behind borders, set ro boa
  // if (adder[adderLength - 1].xPos > 157) {
  //   (adder[adderLength - 1].xPos = 157);
  // }
  //
  // if (adder[adderLength - 1].xPos < 3) {
  //   (adder[adderLength - 1].xPos = 3);
  // }
  // if (adder[adderLength - 1].yPos > 122) {
  //   (adder[adderLength - 1].yPos = 122);
  // }
  //
  // if (adder[adderLength - 1].yPos < 3) {
  //   (adder[adderLength - 1].yPos = 3);
  // }

  // board.drawPoint(adder.getHeadX(), adder.getHeadY());
  // adder[adderLength - 1]
}

Direction getDirection(int xValue, int yValue){

  if(yValue > 980 && currentDirection != DOWN){
    return UP;
  }

  if(yValue < 44 && currentDirection != UP){
    return DOWN;
  }

  if(xValue > 980 && currentDirection != RIGHT){
    return LEFT;
  }

  if(xValue < 44 && currentDirection != LEFT){
    return RIGHT;
  }
  //default return old direction
  return currentDirection;
}
