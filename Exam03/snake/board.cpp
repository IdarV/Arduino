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

uint8_t boardBorderXLeft = 3;
uint8_t boardBorderXRight = 157 + 1; // 22*7 + boardBorderXLeft
uint8_t boardBorderYTop = 3;
uint8_t boardBoarderYBottom = 122 + 1; // 17*7 + boardBorderYTop

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

      TFTscreen.stroke(255, 255, 255);
      // Draw top border left->right
      TFTscreen.line(boardBorderXLeft, boardBorderYTop, boardBorderXRight, boardBorderYTop);
      // Draw right border top->bottom
      TFTscreen.line(boardBorderXLeft, boardBorderYTop, boardBorderXLeft, boardBoarderYBottom);
      // Draw bottom border left->right
      TFTscreen.line(boardBorderXLeft, boardBoarderYBottom, boardBorderXRight, boardBoarderYBottom);
      // Draw left border
      TFTscreen.line(boardBorderXRight, boardBorderYTop, boardBorderXRight, boardBoarderYBottom);

}

void Board::drawPoint(uint8_t xPoint, uint8_t yPoint){
  // set new stroke
  TFTscreen.stroke(rgbColour[0], rgbColour[1], rgbColour[2]);

  //Draw 9x9 square
  for(int i = -3; i <= 3; i++){
    for(int j = -3; j <= 3; j++){
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
  for(int i = -3; i <= 3; i++){
    for(int j = -3; j <= 3; j++){
      TFTscreen.point(xPoint + i, yPoint + j);
    }
  }
}

void Board::drawPellet(Pellet pellet){
  TFTscreen.stroke(56, 3, 200);
  //Draw 9x9 square
  for(int i = -3; i <= 3; i++){
    for(int j = -3; j <= 3; j++){
      TFTscreen.point(pellet.xPos + i, pellet.yPos + j);
    }
  }
  TFTscreen.stroke(0,0,0);
}
