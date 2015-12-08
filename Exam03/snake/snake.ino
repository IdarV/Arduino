/*
Taken stating point in
TFT EtchASketch
http://www.arduino.cc/en/Tutorial/TFTEtchASketch
*/

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

#include "direction.h"

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

TFT TFTscreen = TFT(cs, dc, rst);

// initial position of the cursor
int xPos = 28;
int yPos = 28;

// initial direction
direction currentDirection;
int rgbColour[3];

// pin the erase switch is connected to
int erasePin = 2;
int incColour, decColour;

void setup() {
  Serial.begin(9600);
  // declare inputs
  pinMode(erasePin, INPUT);
  // initialize the screen
  TFTscreen.begin();
  // make the background black
  TFTscreen.background(0, 0, 0);
  // set starting direction
  currentDirection = RIGHT;
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;

  // set inccolor and deccolor;
  decColour = 0;
  incColour = 1;
}

void loop()
{
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

  if(currentDirection == UP){
    yPos += 3;
  }
  else if(currentDirection == DOWN){
    yPos -= 3;
  }

  else if(currentDirection == LEFT){
    xPos -= 3;
  }
  else if(currentDirection == RIGHT){
    xPos += 3;
  }

  // don't let the point go past the screen edges
  if (xPos > 157) {
    (xPos = 157);
  }

  if (xPos < 1) {
    (xPos = 1);
  }
  if (yPos > 124) {
    (yPos = 124);
  }

  if (yPos < 1) {
    (yPos = 1);
  }

  // draw the point
  TFTscreen.stroke(rgbColour[0], rgbColour[1], rgbColour[2]);
  // setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
  // TFTscreen.point(xPos, yPos);

  //Draw 9x9 square
  for(int i = -1; i <= 1; i++){
    for(int j = -1; j <= 1; j++){
      TFTscreen.point(xPos + i, yPos + j);
    }
}
  // read the value of the pin, and erase the screen if pressed
  if (digitalRead(erasePin) == HIGH) {
    TFTscreen.background(0, 0, 0);
  }

  // change color
  // https://gist.github.com/jamesotron/766994
  if(rgbColour[incColour] == 255){
    int temp = incColour;
    incColour = (decColour == 2) ? 0 : decColour + 1;
    decColour = temp;
  }

     rgbColour[decColour] -= 5;
     rgbColour[incColour] += 5;

  delay(33);
}
