#include "sdreader.h"

#define highscorefile_str "A.TXT"
#define notsd_str "!sd"
#define sd_str "sd"
#define nofile_str "no file"
#define file_str "file"

// Initialize sd card
void SDReader::init(int cspin){
  if(!SD.begin(cspin)){
    Serial.println(notsd_str);
  } else{
    Serial.println(sd_str);
  }
}

// Reads highscore from SD card
uint8_t SDReader::readHighscore(){
  // Open the file
  highFile = SD.open(highscorefile_str);
  uint8_t high = 0;

  // Readt the first int from file
  if(highFile) {
    Serial.println(file_str);
    if (highFile.available()) {
      high = (uint8_t) highFile.parseInt();
    }
    highFile.close();
  } else{
    Serial.println(nofile_str);
  }

  return high;
}

// Write highscore to file
void SDReader::setHighscore(uint8_t highscore){
  // Remove existing file
  SD.remove(highscorefile_str);
  // Open (create) file again
  highFile = SD.open(highscorefile_str, FILE_WRITE);

  // Write highscore to it
  if(highFile) {
    highFile.println((int)highscore);
    highFile.close();
  } else{
    Serial.println(nofile_str);
  }
}
