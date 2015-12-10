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

// void SDReader::readFiles(){
//   int numTabs = 0;
//   File dir = SD.open("/");
//   while(true) {
//     Serial.println("while");
//      File entry =  dir.openNextFile();
//      if (! entry) {
//        Serial.println("!entry");
//        // no more files
//        break;
//      }
//      for (uint8_t i=0; i<numTabs; i++) {
//        Serial.print('\t');
//      }
//      Serial.print(entry.name());
//      if (entry.isDirectory()) {
//        Serial.println("/");
//        printDirectory(entry, numTabs+1);
//      } else {
//        // files have sizes, directories do not
//        Serial.print("\t\t");
//        Serial.println(entry.size(), DEC);
//      }
//      entry.close();
//    }
// }
//
// void SDReader::printDirectory(File dir, int numTabs) {
//    while(true) {
//
//      File entry =  dir.openNextFile();
//      if (! entry) {
//        // no more files
//        break;
//      }
//      for (uint8_t i=0; i<numTabs; i++) {
//        Serial.print('\t');
//      }
//      Serial.print(entry.name());
//      if (entry.isDirectory()) {
//        Serial.println("/");
//        printDirectory(entry, numTabs+1);
//      } else {
//        // files have sizes, directories do not
//        Serial.print("\t\t");
//        Serial.println(entry.size(), DEC);
//      }
//      entry.close();
//    }
// }
