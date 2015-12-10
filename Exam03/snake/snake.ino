/*
Taken stating point in
TFT EtchASketch
http://www.arduino.cc/en/Tutorial/TFTEtchASketch
*/

// TODO fix sdreader

#include "Arduino.h"
#include <SD.h>
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include "adder.h"
#include "direction.h"
#include "board.h"
#include "sdreader.h"

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
SDReader sdReader;
Board board;
// Board b = Board(*TFTscreen);
Adder adder;

void setup() {
  Serial.begin(9600);
  sdReader.init(sdcs);

  // Read from SD card
  if(sdReader.fileExists(filename)){
    // Serial.println("SCORES.TXT EXISTS");
  }

  // Set current direction
  currentDirection = RIGHT;

  // Init board
  board.init();

  // Init adder
  adder = Adder(adderSize);

  // Draw adder to screen
  for(int i = 1; i < adder.getLength() - 1; i++){
    board.drawPoint(adder.getBody(i).xPos, adder.getBody(i).yPos);
  }
}

void loop() {
  delay(80);
  // read the potentiometers on A0 and A1
  int xValue = analogRead(A0);
  int yValue = analogRead(A1);

  currentDirection = getDirection(xValue, yValue);
  moveAdder(currentDirection);
}

void moveAdder(Direction direction){
  board.clearPoint(adder.getTailX(), adder.getTailY());

  // START
  for(uint8_t i = 0; i < adder.getLength() -1; i++){
    // adder_body body = adder.getBody(i);
    adder_body nextBody = adder.getBody(i + 1);
    adder.setBody(i, nextBody); //.xPos = adder.getBody(i + 1).xPos;
  //  adder.setBody(i, adder.getBody(i + 1).yPos)//.yPos = adder.getBody(i + 1).yPos;
  }
  uint8_t headX = adder.getHeadX();
  uint8_t headY = adder.getHeadY();
  Serial.println(headY);
  switch(direction){
    case RIGHT:
      headX += 5;
      if (headX > 153) {
        headX = 153;
      }
      break;
    case LEFT:
      if (headX - 5 < 3) {
        headX = 3;
      } else{
        headX -= 5;
      }
      break;
    case UP:
      headY += 5;
      if (headY > 123) {
        headY = 123;
      }
      break;
    case DOWN:
      if (headY - 5 < 3) {
        headY = 3;
      } else{
        headY -= 5;
      }
      break;
  }

  adder.setHeadX(headX);
  adder.setHeadY(headY);

  board.drawPoint(adder.getHeadX(), adder.getHeadY());
  placePellet();
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

void placePellet(){
  randomSeed(analogRead(5));
  int pelletX = random(30) * 5 + 8;
  delay(10);
  int pelletY = random(24) * 5 + 3;
  board.drawPellet(pelletX, pelletY);
}
