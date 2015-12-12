#ifndef SDREADER_H
#define SDREADER_H
#include "Arduino.h"
#include <SD.h>
#include <SPI.h>
class SDReader{
private:
  int cpin;
  void printDirectory(File dir, int numTabs);
public:
  void init(int cspin);
  bool fileExists(char* filename);
  void readFiles();
};
#endif
