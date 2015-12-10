// #include "Arduino.h"
// #include "Arduino.h"
#include "board.h"
#include "direction.h"

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

TFT TFTscreen = TFT(cs, dc, rst);

// RGB
int rgbColour[3];
// RGB to increment and RGB to decrease
int incColour, decColour;

void Board::init(){
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

void Board::drawPoint(uint8_t xPoint, uint8_t yPoint){
  // set new stroke
  TFTscreen.stroke(rgbColour[0], rgbColour[1], rgbColour[2]);

  //Draw 9x9 square
  for(int i = -2; i <= 2; i++){
    for(int j = -2; j <= 2; j++){
      TFTscreen.point(((int)xPoint) + i, ((int)yPoint) + j);
    }
  }

  // set new colors
  if(rgbColour[incColour] == 255){
    int temp = incColour;
    incColour = (decColour == 2) ? 0 : decColour + 1;
    decColour = temp;
  }

  rgbColour[decColour] -= 5;
  rgbColour[incColour] += 5;
}

void Board::clearPoint(int xPoint, int yPoint){
  TFTscreen.stroke(0, 0, 0);
  //Draw 9x9 square
  for(int i = -2; i <= 2; i++){
    for(int j = -2; j <= 2; j++){
      TFTscreen.point(xPoint + i, yPoint + j);
    }
  }
}

void Board::drawPellet(int pelletX, int pelletY){
  TFTscreen.stroke(237, 123, 0);
  //Draw 9x9 square
  for(int i = -2; i <= 2; i++){
    for(int j = -2; j <= 2; j++){
      TFTscreen.point(pelletX + i, pelletY + j);
    }
  }
}
