#include "sdreader.h"

#define highscorefile_str "A.TXT"
#define notsd_str "!sd"
#define sd_str "sd"
#define nofile_str "no file"
#define file_str "file"

void SDReader::init(int cspin){
  // cpin = cspin;
  if(!SD.begin(cspin)){
    Serial.println(notsd_str);
  } else{
    Serial.println(sd_str);
  }
}
uint8_t SDReader::readHighscore(){
  highFile = SD.open(highscorefile_str);
  uint8_t high = 0;

  if(highFile) {
    Serial.println(file_str);
    // read from the file once
    if (highFile.available()) {
      high = (uint8_t) highFile.parseInt();
    }
    highFile.close();
  } else{
    Serial.println(nofile_str);
  }
  return high;
}

void SDReader::setHighscore(uint8_t highscore){
  SD.remove(highscorefile_str);
  highFile = SD.open(highscorefile_str, FILE_WRITE);

  if(highFile) {
    highFile.println((int)highscore);
    highFile.close();
  } else{
    Serial.println(nofile_str);
  }
}
