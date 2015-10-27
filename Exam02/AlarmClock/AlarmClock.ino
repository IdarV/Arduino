#include <Wire.h>
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include "RTClib.h"

#define cs   10
#define dc   9
#define rst  8

TFT TFTscreen = TFT(cs, dc, rst);

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char monthsOfTheYear[12][12] = {"January", "February", "March", "April", "May", "June", "July",
                             "August", "September", "October", "November", "December"};

void setup() {
  Serial.begin(9600);
  //Wire.pins(2, 14); // SDA an SCL (comment on this, source is RTCLib::ds1307
  // Start RTC, print error if it's not found
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.println("RTC time set to compile-date");
  }

  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
}

void clear_text_line(int text_x, int text_y){
  for(int i = 0; i < 16; i++){
    TFTscreen.drawFastHLine(text_x, text_y + i, 100,0x0000);  
  }
}

void loop() {
  DateTime now = rtc.now();
  String timeNow = "";
  timeNow += now.year();
  timeNow += "\n";
  timeNow += monthsOfTheYear[now.month()];
  timeNow += "\n";
  timeNow += (daysOfTheWeek[now.dayOfTheWeek()]);
  timeNow += "\n";
  int now_hour = now.hour();
  if (now_hour < 10) {
    timeNow += "0";
  }
  timeNow += now_hour;
  timeNow += ":";
  timeNow += now.minute();
  timeNow += ":";
  int now_second = now.second();
  if (now_second < 10) {
    timeNow += "0";
  }
  timeNow += now_second;
  Serial.println(timeNow);

  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(0, 0);
  TFTscreen.println(timeNow);
  
  delay(1000);
  clear_text_line(0, 46);

}
