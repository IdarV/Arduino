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

// SDcard cs
int sdcs = 4;

// Adder length
int adderSize = 5;

int buttonPin = 2;
// int buttonState = 0;

uint8_t highscore;

// Sets if the snake just ate a pellet
bool justAte = false;

// Set if snake dies
bool isDead = false;

// Set to true for autoplaying
bool autoPlay = false;

// Autospeed tells how fast to render the autoplay. 0 == normal, 2 == fast
uint8_t autospeed = 0;

// Pellet properties
Pellet pellet;

// Pellets eaten (aka score)
uint8_t pelletsEaten = 0;

// At which direction the snake is currently moving
Direction currentDirection;

// Declares a SD card reader
SDReader sdReader;

// Declares a board
Board board;

// Declares a snake
Adder adder;

void setup() {
  // Set up joystick button
  pinMode(buttonPin, INPUT_PULLUP);
  // Start serial
  Serial.begin(9600);

  // Init, then read from SD card
  sdReader.init(sdcs);
  highscore = sdReader.readHighscore();

  // Set current direction
  currentDirection = RIGHT;

  // Init board
  board.init();

  // Init adder
  adder.init(adderSize);

  // seed random with noise from analog port #5
  randomSeed(analogRead(5));

  // place a pellet at screen
  placeNewPellet();

  // Set highscore
  board.setHighScore(highscore);
}

// For restarting the game, reset values
void resetup(){
  // Reseed random, because why not?
  randomSeed(analogRead(5));

  // Set direction to right
  currentDirection = RIGHT;

  // Reset pellets eaten
  pelletsEaten = 0;

  // Reinitialize board
  board.init();

  // Set highscore
  board.setHighScore(highscore);

  // Reset snake size
  adderSize = 5;

  // Reinitialize snake
  adder.init(adderSize);

  // Place new pellet
  placeNewPellet();
}

void loop() {
  if(autoPlay){
    // Automove i autoplay is set
    automove();
  } else{
    // Delay a bit to get a
    delay(120);
    int xValue = analogRead(A0);
    int yValue = analogRead(A1);

    // Get next direction based on input
    currentDirection = getDirection(xValue, yValue);
  }

  // Move adder, handles death etc.
  moveAdder(currentDirection);

  // The method name speaks for itself =)
  spawnNewPelletIfSnakeIsEatingIt();

}

// Moves the snake in a direction, (kills the snake if it dies)
void moveAdder(Direction direction){
  if(autospeed == 2 && autoPlay){
    // Clear fast if autospeed is set to fast
    board.clearPointFast(adder.getTailX(), adder.getTailY());
  } else{
    // Clear board
    board.clearPoint(adder.getTailX(), adder.getTailY());
  }

  // Move all parts of body one step
  for(int i = 0; i < adder.getLength() -1; i++){
    adder_body nextBody = adder.getBody(i + 1);
    adder.setBody(i, nextBody);
  }

  // Extract head resources
  uint8_t headX = adder.getHeadX();
  uint8_t headY = adder.getHeadY();

  // Move head in the right direction. Set to dead if out of bounds
  switch(direction){
    case RIGHT:
    headX += 7;
    if (headX > 154) {
      isDead = true;
    }
    break;
    case LEFT:
    if (headX - 7 < 56) {
      isDead = true;
    } else{
      headX -= 7;
    }
    break;
    case UP:
    headY += 7;
    if (headY > 119) {
      isDead = true;
    }
    break;
    case DOWN:
    if (headY - 7 < 14) {
      isDead = true;
    } else{
      headY -= 7;
    }
    break;
  }

  // If snake just ate a pellet, make it bigger
  if(justAte){
      adder.grow();
      justAte = false;
  }

  // Set head to new properties
  adder.setHeadX(headX);
  adder.setHeadY(headY);

  if(autospeed == 2 && autoPlay){
    // Draw head fast if autospeed is set to fast
    board.drawPointFast(adder.getHeadX(), adder.getHeadY());
  } else {
    // Draw new head
    board.drawPoint(adder.getHeadX(), adder.getHeadY());
  }

  // End game if player died or score is maxscore
  if(isDead || pelletsEaten == 223){
    die();
    isDead = false;
  }

}

// Returns next direction
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

  // Default return old direction
  return currentDirection;
}

// Places a new pellet on a random part of the screen
void placeNewPellet(){
  /* Keep trying new random positions until we get a position that doesn't have
   snake on it */
  do{
    pellet.xPos = random(15) * 7 + 56;
    delay(10);
    pellet.yPos = random(15) * 7 + 14;
  } while(adder.isPositionedAt(pellet.xPos, pellet.yPos));


  if(autospeed == 2 && autoPlay){
    // Draw pellet fast if autospeed is set to fast
    board.drawPelletFast(pellet);
  } else{
    // Draw pellet
    board.drawPellet(pellet);
  }

}

void spawnNewPelletIfSnakeIsEatingIt(){
  /* If adder's position is the same as pellets position, mark as eaten and
  increase score */
  if(adder.getHeadX() == pellet.xPos && adder.getHeadY() == pellet.yPos){
    justAte = true;
    pelletsEaten++;

    placeNewPellet();

    // Play a little beep when eating a pellet
    tone(7, 800, 250);
    board.setScore(pelletsEaten);
  }
}

// Script for auto moving the snake
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

// Shows the die screen while button is not pressed
void die(){
  bool newHigh = pelletsEaten > highscore;
  if(newHigh){
    sdReader.setHighscore(pelletsEaten);
    highscore = pelletsEaten;
  }
  while(digitalRead(buttonPin)){
    board.winScreen(pelletsEaten, newHigh); // pelletsEaten > highscore
    delay(1000);
  }
  resetup();
}
