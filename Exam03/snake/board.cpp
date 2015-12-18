#include "board.h"
#include "direction.h"

// Pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

// Strings
#define score_str "Score"
#define high_str "High"
#define uwin_str "GAMEOVER"
#define newHighscore "New highscore!"
#define pressagain_str "Press joystick to restart"

TFT TFTscreen = TFT(cs, dc, rst);

// RGB
uint8_t rgbColour[3];
// RGB to increment and RGB to decrease
uint8_t incColour, decColour;

void Board::init(){
  // Start screen
  TFTscreen.begin();
  // make the background black
  TFTscreen.background(0, 0, 0);

  // Set starting colors
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;

  // Set which color to be incremented and decremented
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
  TFTscreen.setTextSize(1);
  TFTscreen.print(score_str);
  setScore(0);

  // Write highscore
  TFTscreen.setTextSize(1);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setCursor(10, 50);
  TFTscreen.print(high_str);
  TFTscreen.setCursor(10, 60);
  TFTscreen.print(score_str);
}

// Prints score to screen
void Board::setScore(uint8_t score){
  TFTscreen.setTextSize(3);
  TFTscreen.setCursor(0, 20);

  // Write old score as black, which erases it
  if(score != 0){
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.print(score - 1);
  }

  // Write new score in color of snake
  TFTscreen.setCursor(0, 20);
  TFTscreen.stroke(rgbColour[0], rgbColour[1], rgbColour[2]);
  TFTscreen.print(score);

  // Reset cursor size
  TFTscreen.setTextSize(1);
}

// Prints highscore to screen
void Board::setHighScore(uint8_t highscore){
  TFTscreen.stroke(0, 72, 255);
  TFTscreen.setCursor(0, 70);

  TFTscreen.setTextSize(3);
  TFTscreen.print(highscore);

  TFTscreen.setTextSize(1);
}

// Draws a 9X9 point with (xPoint, yPoint) as center
void Board::drawPoint(uint8_t xPoint, uint8_t yPoint){
  // set new stroke
  TFTscreen.stroke(rgbColour[0], rgbColour[1], rgbColour[2]);

  //Draw 9x9 square
  for(int i = -3; i <= 3; i++){
    for(int j = -3; j <= 3; j++){
      TFTscreen.point(((int)xPoint) + i, ((int)yPoint) + j);
    }
  }

  // Set new colors
  updateColors();
}

// Draws snake body as single point(1 pixel)
void Board::drawPointFast(uint8_t xPoint, uint8_t yPoint){
  // Set new stroke
  TFTscreen.stroke(rgbColour[0], rgbColour[1], rgbColour[2]);

  // Draw 9x9 square
  TFTscreen.point(xPoint, yPoint);

  // Set new colors
  updateColors();
}

// Clear (draw black) 9x9 square
void Board::clearPoint(int xPoint, int yPoint){
  TFTscreen.stroke(0, 0, 0);
  for(int i = -3; i <= 3; i++){
    for(int j = -3; j <= 3; j++){
      TFTscreen.point(xPoint + i, yPoint + j);
    }
  }
}

// Clear (draw black) single point (1 pixel)
void Board::clearPointFast(int xPoint, int yPoint){
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.point(xPoint, yPoint);
}

// Draw a 9x9 pellet
void Board::drawPellet(Pellet pellet){
  TFTscreen.stroke(56, 3, 200);
  for(int i = -3; i <= 3; i++){
    for(int j = -3; j <= 3; j++){
      TFTscreen.point(pellet.xPos + i, pellet.yPos + j);
    }
  }
  TFTscreen.stroke(0,0,0);
}

// Draws pellet as only the middle pixel
void Board::drawPelletFast(Pellet pellet){
  TFTscreen.stroke(56, 3, 200);
  TFTscreen.point(pellet.xPos, pellet.yPos);
  TFTscreen.stroke(0,0,0);
}

void Board::winScreen(uint8_t highscore, bool isNewHighscore){
  // Set background color to random
  TFTscreen.background(random(255), random(255), random(255));

  // Print "game over"
  TFTscreen.setTextSize(3);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setCursor(0, 40);
  TFTscreen.print(uwin_str);


  // Print "press joystick to restart"
  TFTscreen.setTextSize(1);
  TFTscreen.setCursor(0, 10);
  TFTscreen.print(pressagain_str);

  // Print score
  TFTscreen.setCursor(0, 80);
  TFTscreen.setTextSize(2);
  TFTscreen.print(score_str);
  TFTscreen.print(": ");
  TFTscreen.print(highscore);

  // If score is new highcore, print "new highscore!"
  if(isNewHighscore){
    TFTscreen.setTextSize(1);
    TFTscreen.setCursor(0, 100);
    TFTscreen.print(newHighscore);
  }
}

// Update cycling colors
void Board::updateColors(){
  if(rgbColour[incColour] == 255){
    int temp = incColour;
    incColour = (decColour == 2) ? 0 : decColour + 1;
    decColour = temp;
  }

  rgbColour[decColour] -= 5;
  rgbColour[incColour] += 5;
}
