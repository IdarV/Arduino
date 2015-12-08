/*
Taken stating point in
TFT EtchASketch
http://www.arduino.cc/en/Tutorial/TFTEtchASketch
*/

#include "Arduino.h"
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include "direction.h"
#include "board.h"

// initial position of the cursor
int xPos = 28;
int yPos = 28;

Direction currentDirection;
Board board;

void setup() {
  // Serial.begin(9600);

  // set starting direction
  currentDirection = RIGHT;

  // create board
  // board = Board(BOARD_HEIGHT, BOARD_WIDTH);
  board = Board(126, 160);
}

void loop() {
  delay(100);
  // read the potentiometers on A0 and A1
  int xValue = analogRead(A0);
  int yValue = analogRead(A1);

  if(yValue > 980 && currentDirection != DOWN){
    currentDirection = UP;
  } else if(yValue < 44 && currentDirection != UP){
    currentDirection = DOWN;
  } else if(xValue > 980 && currentDirection != RIGHT){
    currentDirection = LEFT;
  } else if(xValue < 44 && currentDirection != LEFT){
    currentDirection = RIGHT;
  }

  board.drawPellet(currentDirection);

  delay(33);
}
