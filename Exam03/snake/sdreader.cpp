#include "sdreader.h"
#include <SPI.h>
#include <SD.h>

void SDReader::init(int cspin){
  cpin = cspin;
}
bool SDReader::fileExists(char* filename){

  Serial.println("fe");
  if(!SD.begin(cpin)){
    Serial.println("!sd");
    Serial.println(filename);
    Serial.println(cpin);
    return false;
  }

  return SD.exists(filename);
}
