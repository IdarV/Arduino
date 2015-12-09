// #include "Arduino.h"
#include "board.h"
#include "direction.h"
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

TFT TFTscreen = TFT(cs, dc, rst);

int height, width;
// int xPos, int yPos;

// RGB
int rgbColour[3];
// RGB to increment and RGB to decrease
int incColour, decColour;

Board::Board(){
}

Board::Board(int a_height, int a_width){
  height = a_height;
  width = a_width;

  TFTscreen.begin();
  // make the background black
  TFTscreen.background(0, 0, 0);

  // Set starting colors
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;

  decColour = 0;
  incColour = 1;
}

void  Board::setStartPositions(int a_startingPositionX, int a_startingPositionY){
  xPos = a_startingPositionX;
  yPos = a_startingPositionY;
}

void Board::drawPellet(Direction direction){

  applyDirection(direction);

  drawSquare();

  // set new colors
  if(rgbColour[incColour] == 255){
    int temp = incColour;
    incColour = (decColour == 2) ? 0 : decColour + 1;
    decColour = temp;
  }

  rgbColour[decColour] -= 5;
  rgbColour[incColour] += 5;

}


void Board::applyDirection(Direction direction){
  // Update positions
  if(direction == UP){
    yPos += 3;
  }
  else if(direction == DOWN){
    yPos -= 3;
  }

  else if(direction == LEFT){
    xPos -= 3;
  }
  else if(direction == RIGHT){
    xPos += 3;
  }

  // If behind borders, set ro boa
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
}

void Board::drawSquare(){
  // set new stroke
  TFTscreen.stroke(rgbColour[0], rgbColour[1], rgbColour[2]);
  //Draw 9x9 square
  for(int i = -1; i <= 1; i++){
    for(int j = -1; j <= 1; j++){
      TFTscreen.point(xPos + i, yPos + j);
    }
  }
}
