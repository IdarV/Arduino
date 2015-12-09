#ifndef BOARD_H
#define BOARD_H
  #include <TFT.h>
  #include "direction.h"

  class Board{
  private:
    int height, width;
    int xPos, yPos;
    void applyDirection(Direction direction);
    void drawSquare();
  public:
    Board();
    Board(int height, int width);
    void setStartPositions(int x, int y);
    void drawPellet(Direction direction);
  };
#endif
