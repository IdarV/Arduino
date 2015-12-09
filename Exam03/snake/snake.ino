/*
Taken stating point in
TFT EtchASketch
http://www.arduino.cc/en/Tutorial/TFTEtchASketch
*/

#include "Arduino.h"
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <SD.h>
#include "direction.h"
#include "board.h"
#include "sdreader.h"
#include "adder.h"

// initial position of the cursor
int xPos = 28;
int yPos = 28;

// scores file
char* filename = "SCORES.TXT";

// SDcard cs
int sdcs = 4;

// Adder length
int adderLength = 5;

Direction currentDirection;
// SDReader sdReader;
SDReader sdReader;
Board board;
adder_body *adder;

void setup() {
  // Serial.begin(9600);
  // Serial.println(sizeof(int));
  // set starting direction
  currentDirection = RIGHT;
  board = Board(126, 160);
  adder = new adder_body[5];
  for(int i = 0; i < adderLength; i++){
    adder[i].xPos = 28 + 5*i;
    adder[i].yPos = 28;

    board.drawPoint(adder[i].xPos, adder[i].yPos);
  }

  sdReader = SDReader(4);
  sdReader.readFiles();

  // create board
  // board = Board(BOARD_HEIGHT, BOARD_WIDTH);
}

void loop() {
  delay(80);
  // read the potentiometers on A0 and A1
  int xValue = analogRead(A0);
  int yValue = analogRead(A1);

  currentDirection = getDirection(xValue, yValue);
  // for(int i = 0; i < 5; i++){
  //   adder[i].xPos = 28 + 5*i;
  //   adder[i].yPos = 28;
  //
  //   board.drawPoint(adder[i].xPos, adder[i].yPos);
  // }
  //
  // board.moveAdder(adder[i], adder[adderLength - 1]);
  moveAdder(currentDirection);

  //board.drawPellet(currentDirection);
}

void moveAdder(Direction direction){
  board.clearPoint(adder[0].xPos, adder[0].yPos);

  for(int i = 0; i < adderLength -1; i++){
    adder[i].xPos = adder[i + 1].xPos;
    adder[i].yPos = adder[i + 1].yPos;
  }
  switch(direction){
    case RIGHT:
      adder[adderLength - 1].xPos += 5;
      break;
    case LEFT:
      adder[adderLength - 1].xPos -= 5;
      break;
    case UP:
      adder[adderLength - 1].yPos += 5;
      break;
    case DOWN:
      adder[adderLength - 1].yPos -= 5;
      break;
  }

  board.drawPoint(adder[adderLength - 1].xPos, adder[adderLength - 1].yPos);
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
