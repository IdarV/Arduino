/*

TFT EtchASketch

This example for the Arduino screen draws a white point
on the GLCD based on the values of 2 potentiometers.
To clear the screen, press a button attached to pin 2.

This example code is in the public domain.

Created 15 April 2013 by Scott Fitzgerald

http://www.arduino.cc/en/Tutorial/TFTEtchASketch

*/

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

enum direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

TFT TFTscreen = TFT(cs, dc, rst);

// initial position of the cursor
int xPos = TFTscreen.width() / 2;
int yPos = TFTscreen.height() / 2;

// initial direction
direction currentDirection = RIGHT;

// pin the erase switch is connected to
int erasePin = 2;

void setup() {
  Serial.begin(9600);
  // declare inputs
  pinMode(erasePin, INPUT);
  // initialize the screen
  TFTscreen.begin();
  // make the background black
  TFTscreen.background(0, 0, 0);
  // set starting direction

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
    yPos += 1;
  }
  else if(currentDirection == DOWN){
    yPos -= 1;
  }

  else if(currentDirection == LEFT){
    xPos -= 1;
  }
  else if(currentDirection == RIGHT){
    xPos += 1;
  }

  // don't let the point go past the screen edges
  if (xPos > 159) {
    (xPos = 159);
  }

  if (xPos < 0) {
    (xPos = 0);
  }
  if (yPos > 127) {
    (yPos = 127);
  }

  if (yPos < 0) {
    (yPos = 0);
  }

  Serial.println(currentDirection);

  // draw the point
  TFTscreen.stroke(255, 255, 255);
  // TFTscreen.point(xPos, yPos);
  TFTscreen.point(xPos, yPos);

  // read the value of the pin, and erase the screen if pressed
  if (digitalRead(erasePin) == HIGH) {
    TFTscreen.background(0, 0, 0);
  }

  delay(33);
}
