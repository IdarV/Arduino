#ifndef BOARD_H
#define BOARD_H
  // #include "Arduino.h"
  #include <TFT.h>
  #include <SPI.h>
  #include "direction.h"
  #include "pellet.h"

  class Board{
  private:
  public:
    void init();
    void drawPoint(uint8_t xPoint, uint8_t yPoint);
    void clearPoint(int xPoint, int yPoint);
    void drawPellet(Pellet pellet);
  };
#endif
