#ifndef BOARD_H
#define BOARD_H
  #include "Arduino.h"
  #include <TFT.h>
  #include <SPI.h>
  #include "direction.h"
  #include "pellet.h"

  class Board{
  private:
  // uint8_t boardBorderXLeft = 3;
  uint8_t boardBorderXLeft = 3 + 7*7;
  uint8_t boardBorderXRight = 158; // 22*7 + boardBorderXLeft
  uint8_t boardBorderYTop = 3 + 7;
  uint8_t boardBoarderYBottom = 123; // 16*7 + boardBorderYTop
  public:
    void init();
    void drawPoint(uint8_t xPoint, uint8_t yPoint);
    void drawPointFast(uint8_t xPoint, uint8_t yPoint);
    void clearPoint(int xPoint, int yPoint);
    void clearPointFast(int xPoint, int yPoint);
    void drawPellet(Pellet pellet);
    void drawPelletFast(Pellet pellet);
    void winScreen(uint8_t highscore, bool isNewHighscore);
    void setScore(uint8_t score);
    void setHighScore(uint8_t highscore);

  private:
    void updateColors();
  };
#endif
