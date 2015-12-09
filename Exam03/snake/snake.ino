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

// initial position of the cursor
int xPos = 28;
int yPos = 28;

// SDcard cs
int sdcs = 4;

Direction currentDirection;
// SDReader sdReader;
SDReader sdReader = SDReader(4);
Board board;

void setup() {
  Serial.begin(9600);
  // Serial.println(sizeof(int));
  // set starting direction
  currentDirection = RIGHT;

  // sdReader = SDReader(4);
  if(sdReader.fileExists("highscores.txt")){
    Serial.println("file exists");
  } else{
    Serial.println("file doesn't exist");
  }

  sdReader.readFiles();

  // create board
  // board = Board(BOARD_HEIGHT, BOARD_WIDTH);
  board = Board(126, 160);
}

void loop() {
  delay(80);
  // read the potentiometers on A0 and A1
  int xValue = analogRead(A0);
  int yValue = analogRead(A1);

  currentDirection = getDirection(xValue, yValue);

  board.drawPellet(currentDirection);
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
