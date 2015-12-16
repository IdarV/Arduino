#include "board.h"
#include "direction.h"

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

#define score_str "Score"
#define high_str "High"
#define uwin_str "u win"

TFT TFTscreen = TFT(cs, dc, rst);

// RGB
uint8_t rgbColour[3];
// RGB to increment and RGB to decrease
uint8_t incColour, decColour;

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

      // Write score
      TFTscreen.setCursor(10, 10);
      TFTscreen.print(score_str);
      setScore(0);


}

void Board::setScore(uint8_t score){
  TFTscreen.setCursor(10, 20);
  if(score != 0){
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.print(score - 1);
  }
  TFTscreen.setCursor(10, 20);

  TFTscreen.stroke(rgbColour[0], rgbColour[1], rgbColour[2]);
  TFTscreen.print(score);


}

void Board::setHighScore(uint8_t highscore){
  TFTscreen.stroke(0, 72, 255);
  TFTscreen.setCursor(10, 50);
  TFTscreen.print(high_str);
  TFTscreen.setCursor(10, 60);
  TFTscreen.print(score_str);
  TFTscreen.setCursor(10, 70);
  TFTscreen.print(highscore);
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

void Board::drawPointFast(uint8_t xPoint, uint8_t yPoint){
  // set new stroke
  TFTscreen.stroke(rgbColour[0], rgbColour[1], rgbColour[2]);

  //Draw 9x9 square
  TFTscreen.point(xPoint, yPoint);
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

void Board::clearPointFast(int xPoint, int yPoint){
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.point(xPoint, yPoint);
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

void Board::drawPelletFast(Pellet pellet){
  TFTscreen.stroke(56, 3, 200);
  TFTscreen.point(pellet.xPos, pellet.yPos);
  TFTscreen.stroke(0,0,0);
}

void Board::winScreen(){
  TFTscreen.background(0, 255, 0);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setCursor(80, 80);
  TFTscreen.print(uwin_str);
}
