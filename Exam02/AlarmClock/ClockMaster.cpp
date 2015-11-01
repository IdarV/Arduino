#include "ClockMaster.h"
#include "Alarm.h"
#include <TFT.h>  // Arduino LCD library

#define cs   10
#define dc   9
#define rst  8

RTC_DS1307 rtc;

// Init screen
TFT tft = TFT(cs, dc, rst);

char daysOfTheWeek[7][12] =
{"Sunday", "Monday", "Tuesday", "Wednesday",
 "Thursday", "Friday", "Saturday"};
char monthsOfTheYear[12][12] =
{"January", "February", "March", "April", "May", "June", "July",
"August", "September", "October", "November", "December"};

// SCREEN SETTINGS
int defaultBackground = 0x0000;
int lastAlarmXPos = -1;

// YEAR SETTINGS
int yearSize = 2;
int yearXPos = 114;
int yearYPos = 110;
int yearLength = 48;

// MONTH SETTINGS
int monthSize = 2;
int monthXPos = 0;
int monthYPos = 0;
int monthLength = 96;

// DAY OF MONTH SETTINGS
int daySize = 2;
int dayXPos = monthLength + 4; // One space after month
int dayYPos = 0;
int dayLength = 24;

// Weekday SETTINGS
int weekdayColor = 0xFF00FF;
int weekdaySize = 2;
int weekdayXPos = 0; // One space after month
int weekdayYPos = 112;
int weekdayLength = 110;

// HOUR SETTINGS
int hourLeftOffset = 11;
int hourSize = 4;
int hourXPos = 0 + hourLeftOffset;
int hourYPos = 50;
int hourLength = 48;

// Minute SETTINGS
int minuteColor = 0xFF00FF;
int minuteSize = 4;
int minuteXPos = hourLength + hourLeftOffset;
int minuteYPos = 50;
int minuteLength = 48;

// Second SETTINGS
int secondSize = 4;
int secondXPos = minuteXPos + minuteLength;
int secondYPos = 50;
int secondLength = 48;

void clearTextLine(int textX, int textY, int textSize, int textLength) {
  for (int i = 0; i < (8 * textSize); i++) {
    tft.drawFastHLine(textX, textY + i, textLength, defaultBackground);
  }
}

void writeMonth(DateTime time_now) {
  tft.stroke(255, 255, 255);
  tft.setTextSize(monthSize);
  tft.setCursor(monthXPos, monthYPos);

  //monthLength = monthsOfTheYear[time_now.month() - 1].size * 8;

  tft.print(monthsOfTheYear[time_now.month() - 1]);
}

void writeYear(DateTime time_now) {
  tft.stroke(255, 255, 255);
  tft.setTextSize(yearSize);
  tft.setCursor(yearYPos, yearXPos);

  tft.print(time_now.year());
}

void writeDay(DateTime time_now) {
  dayXPos = monthLength + 4; // One space after month
  tft.stroke(255, 255, 255);
  tft.setTextSize(daySize);
  tft.setCursor(dayXPos, dayYPos);

  if (time_now.day() < 10) {
    tft.print("0");
  }

  tft.print(time_now.day());
}

void writeWeekDay(DateTime time_now){
  tft.stroke(weekdayColor);
  tft.setTextSize(weekdaySize);
  tft.setCursor(weekdayXPos, weekdayYPos);

  tft.print(daysOfTheWeek[time_now.dayOfTheWeek()]);
}

void writeHour(DateTime time_now) {
  tft.stroke(255, 255, 255);
  tft.setTextSize(hourSize);
  tft.setCursor(hourXPos, hourYPos);

  if (time_now.hour() < 10) {
    tft.print("0");
  }

  tft.print(time_now.hour());
}

void writeMinute(DateTime time_now) {
  tft.stroke(minuteColor);
  tft.setTextSize(hourSize);
  tft.setCursor(minuteXPos, minuteYPos);
  if (time_now.minute() < 10) {
    tft.print("0");
  }
  tft.print(time_now.minute());
}

void writeSecond(DateTime time_now) {
  tft.stroke(255, 255, 255);
  tft.setTextSize(secondSize);
  tft.setCursor(secondXPos, secondYPos);
  if (time_now.second() < 10) {
    tft.print("0");
  }
  tft.print(time_now.second());
}

DateTime getTime(){
  return rtc.now() + TimeSpan(0, 0, 21, 16);//timeDifference;
}

void initScreen(){
  tft.background(0, 0, 0);
  DateTime time_now = getTime();

  writeSecond(time_now);
  writeMinute(time_now);
  writeHour(time_now);
  writeDay(time_now);
  writeWeekDay(time_now);
  writeMonth(time_now);
  writeYear(time_now);
}

void initRTC(){
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
}

void clockSetup(Alarm *alarm) {
  Serial.begin(9600);
  initRTC();
  tft.begin();
  initScreen();
  alarm->initAlarm(getTime());
}

void waitForNextSecond(DateTime time_now, Alarm *alarm){
  // Wait for new second (I like this better than delay(1000), because it takes loop execution time into account)
  while(getTime().second() == time_now.second()){
    // If time is past alarm time, and the alarm state is still active
    if(alarm->getAlarm().unixtime() <= time_now.unixtime() && !alarm->alarmState()){
      // If alarm-button is turend off, turn alarm off
      if(alarm->alarmButtonIsPressed()){
        alarm->setAlarmButtonState(1);
      }
      // Sound the canons
      alarm->ring();
    }
    delay(10);
  }
}

// secondy: 50
void resetDisplayTime(DateTime newTime, int currentXPos){

  clearTextLine(secondXPos, secondYPos, secondSize, secondLength);
  writeSecond(newTime);

  clearTextLine(minuteXPos, minuteYPos, minuteSize, minuteLength);
  writeMinute(newTime);

  clearTextLine(hourXPos, hourYPos, hourSize, hourLength);
  writeHour(newTime);

  clearTextLine(dayXPos, dayYPos, daySize, dayLength);
  clearTextLine(weekdayXPos, weekdayYPos, weekdaySize, weekdayLength);
  writeDay(newTime);
  writeWeekDay(newTime);

  clearTextLine(monthXPos, monthYPos, monthSize, monthLength);
  writeMonth(newTime);

  clearTextLine(yearXPos, yearYPos, yearSize, yearLength);
  writeYear(newTime);

  // draw current x-position-indicator
  if(lastAlarmXPos != currentXPos){
    // Center x-position-indicator under current number being changed
    clearTextLine(0, 85, 2, 160);
    if(currentXPos != -1){  
      int calculatedXPos = 45 * currentXPos + 30;
      tft.setCursor(calculatedXPos, 85);
      tft.print("-");
    }
  }

  lastAlarmXPos = currentXPos;
}

void updateDisplayTime(DateTime time_now){
  clearTextLine(secondXPos, secondYPos, secondSize, secondLength);
  writeSecond(time_now);

  // If second is 0, change the minute aswell
  if (time_now.second() == 0) {
    clearTextLine(minuteXPos, minuteYPos, minuteSize, minuteLength);
    writeMinute(time_now);

    // If the second is 0 AND minute is 0, bump the hour up
    if (time_now.minute() == 0) {
      clearTextLine(hourXPos, hourYPos, hourSize, hourLength);
      writeHour(time_now);

      // If the second is 0 AND the minute is 0 AND the hour is 0, skip to next day
      if (time_now.hour() == 0) {
        clearTextLine(dayXPos, dayYPos, daySize, dayLength);
        clearTextLine(weekdayXPos, weekdayYPos, weekdaySize, weekdayLength);
        writeDay(time_now);
        writeWeekDay(time_now);

        // If the second is 0 AND the minute is 0 AND the hour is 0 AND the day is 1, skip to next day (preferebly friday at 6pm)
        if (time_now.day() == 1) {
          clearTextLine(monthXPos, monthYPos, monthSize, monthLength);
          writeMonth(time_now);

          // If the second is 0 AND the minute is 0 AND the hour is 0 AND the day is 1 AND the month is 1, skip to next year and RIDE YOUR HOVERBOARDS
          if (time_now.month() == 1) {
            clearTextLine(yearXPos, yearYPos, yearSize, yearLength);
            writeYear(time_now);
          }
        }
      }
    }
  }
}
