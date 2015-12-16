#include "sdreader.h"

#define highscorefile_str "A.TXT"
#define notsd_str "!sd"
#define sd_str "sd"

void SDReader::init(int cspin){
  // cpin = cspin;
  if(!SD.begin(cspin)){
    Serial.println(notsd_str);
    Serial.println(cspin);
  } else{
    Serial.println(sd_str);
  }
}
uint8_t SDReader::readHighscore(){
  highFile = SD.open(highscorefile_str);
  uint8_t high = 0;

  if(highFile) {
    Serial.print(notsd_str);
    // read from the file once
    if (highFile.available()) {
      high = (uint8_t) highFile.parseInt();
    }
    highFile.close();
  } else{
    Serial.println(highscorefile_str);
  }
  return high;
}
