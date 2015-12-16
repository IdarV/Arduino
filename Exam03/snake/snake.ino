/*
Taken stating point in
TFT EtchASketch
http://www.arduino.cc/en/Tutorial/TFTEtchASketch
*/

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <TFT.h>
#include "adder.h"
#include "direction.h"
#include "board.h"
#include "sdreader.h"
#include "pellet.h"

// scores file
char *filename = "A.TXT";

// SDcard cs
int sdcs = 4;

int soundPin = 7;

// Adder length
int adderSize = 5;

// Sets if the snake just ate a pellet
bool justAte = false;

// Uncomment for autoplaying
bool autoPlay = true;
// 0 == fast, 2 == superfast
uint8_t autospeed = 2;

// Pellet properties
Pellet pellet;
uint8_t pelletsEaten = 0;

Direction currentDirection;
SDReader sdReader;
Board board;
Adder adder;

void setup() {
  Serial.begin(9600);
  // Serial.println(sizeof(uint8_t));
  sdReader.init(sdcs);
  // Read from SD card
  if(sdReader.fileExists(filename)){
    Serial.print(filename);
    // Serial.println(" exists");
  } else{
    // Serial.println(" does not exist");
  }

  // Set current direction
  // currentDirection = RIGHT;

  // Setup for automove
  currentDirection = LEFT;

  // Init board
  board.init();

  // Init adder
  adder = Adder(adderSize);

  // seed random func
  randomSeed(analogRead(5));

  // Draw adder to screen
  // for(int i = 1; i < adder.getLength() - 1; i++){
  //   board.drawPoint(adder.getBody(i).xPos, adder.getBody(i).yPos);
  // }

  // place a pellet at screen
  placeNewPellet();
}

void loop() {
  // FOR PLAYING
  if(autoPlay){
    automove();
  } else{
    delay(120);
    int xValue = analogRead(A0);
    int yValue = analogRead(A1);
    currentDirection = getDirection(xValue, yValue);
  }

  moveAdder(currentDirection);

  spawnNewPelletIfSnakeIsEatingIt();

  while(pelletsEaten == 223){
    board.winScreen();
    delay(10000);
  }
  //
  // Serial.print(adder.getHeadX());
  // Serial.print(", ");
  // Serial.println(adder.getHeadY());
}

void moveAdder(Direction direction){
  if(autospeed == 2 && autoPlay){
    board.clearPointFast(adder.getTailX(), adder.getTailY());
  } else{
    board.clearPoint(adder.getTailX(), adder.getTailY());
  }

  // START
  for(int i = 0; i < adder.getLength() -1; i++){
    adder_body nextBody = adder.getBody(i + 1);
    adder.setBody(i, nextBody);
  }

  uint8_t headX = adder.getHeadX();
  uint8_t headY = adder.getHeadY();
  switch(direction){
    case RIGHT:
    headX += 7;
    if (headX > 154) {
      headX = 154;
    }
    break;
    case LEFT:
    if (headX - 7 < 56) {
      headX = 56;
    } else{
      headX -= 7;
    }
    break;
    case UP:
    headY += 7;
    if (headY > 119) {
      headY = 119;
    }
    break;
    case DOWN:
    if (headY - 7 < 14) {
      headY = 14;
    } else{
      headY -= 7;
    }
    break;
  }


  if(justAte){
      adder.grow();
      justAte = false;
  }

  adder.setHeadX(headX);
  adder.setHeadY(headY);

  if(autospeed == 2 && autoPlay){
    board.drawPointFast(adder.getHeadX(), adder.getHeadY());
  } else {
    board.drawPoint(adder.getHeadX(), adder.getHeadY());
  }

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

void placeNewPellet(){
  do{
    pellet.xPos = random(15) * 7 + 56;
    delay(10);
    pellet.yPos = random(15) * 7 + 14;
  } while(adder.isPositionedAt(pellet.xPos, pellet.yPos));

  // Serial.print("Pellet spawned at ");
  // Serial.print(pellet.xPos);
  // Serial.print(", ");
  // Serial.println(pellet.yPos);


  // board.drawPellet(pellet);if(autospeed == 2){
  if(autospeed == 2 && autoPlay){
    board.drawPelletFast(pellet);
  } else{
    board.drawPellet(pellet);
  }

}

void spawnNewPelletIfSnakeIsEatingIt(){
  if(adder.getHeadX() == pellet.xPos && adder.getHeadY() == pellet.yPos){
    justAte = true;
    pelletsEaten++;
    Serial.print("Pellets: ");
    Serial.println(pelletsEaten);
    placeNewPellet();
    tone(7, 800, 250);
    board.setScore(pelletsEaten);
  }
}

void automove(){
  if(adder.getHeadX() == 147 && adder.getHeadY() == 119){
    moveAdder(RIGHT);
    spawnNewPelletIfSnakeIsEatingIt();
    for(int i = 0; i < 15; i++){
      moveAdder(DOWN);
      spawnNewPelletIfSnakeIsEatingIt();
    }
    moveAdder(LEFT);
    spawnNewPelletIfSnakeIsEatingIt();
    currentDirection = LEFT;
  }
  else if(adder.getHeadX() == 147){
    moveAdder(UP);
    spawnNewPelletIfSnakeIsEatingIt();
    currentDirection = LEFT;
  }

  else if(adder.getHeadX() == 56){
    moveAdder(UP);
    spawnNewPelletIfSnakeIsEatingIt();
    currentDirection = RIGHT;
  }
}
