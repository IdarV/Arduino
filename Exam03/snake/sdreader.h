#ifndef SDREADER_H
#define SDREADER_H
#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

class SDReader{
private:
  File highFile;
public:
  void init(int cspin);
  uint8_t readHighscore();
};
#endif
