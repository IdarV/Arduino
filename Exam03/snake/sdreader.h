#ifndef SDREADER_H
#define SDREADER_H
#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
class SDReader{
private:
  int cpin;
  Sd2Card card;
  void printDirectory(File dir, int numTabs);
public:
  void init(int cspin);
  bool fileExists(char* filename);
  void readFiles();
};
#endif
