#ifndef BOARD_H
#define BOARD_H
  // #include "Arduino.h"
  #include <TFT.h>
  #include <SPI.h>
  #include "direction.h"

  class Board{
  private:
    int height, width;
    int xPos, yPos;
    void applyDirection(Direction direction);
    void drawSquare();
  public:
    void init();
    void setStartPositions(int x, int y);
    void drawPellet(Direction direction);
    void drawPoint(uint8_t xPoint, uint8_t yPoint);
    void clearPoint(int xPoint, int yPoint);
  };
#endif
