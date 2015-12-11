#include "sdreader.h"
#include <SPI.h>
#include <SD.h>

void SDReader::init(int cspin){
  cpin = cspin;
}
bool SDReader::fileExists(char* filename){
  SD.begin(cpin);
  return SD.exists(filename);
}
