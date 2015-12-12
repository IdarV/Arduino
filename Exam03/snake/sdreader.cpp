#include "sdreader.h"
// #include <SPI.h>
// #include <SD.h>

void SDReader::init(int cspin){
  cpin = cspin;
}
bool SDReader::fileExists(char* filename){
  if(!SD.begin(cpin)){
    return false;
  }
  return SD.exists(filename);
}
