#ifndef ClockMasterHeadFile
#define ClockMasterHeadFile
#include <Wire.h>
#include "Alarm.h"
#include "RTClib.h"

class ClockMaster{
public:
  void clockSetup(Alarm *alarm);
  DateTime getTime();
  void updateDisplayTime(DateTime time_now);
  void waitForNextSecond(DateTime time_now, Alarm *alarm);
  void resetDisplayTime(DateTime newTime, int currentXPos);
  void initScreen();
private:
  void initRTC();
  void clearTextLine(int textX, int textY, int textSize, int textLength);

  void writeMonth(DateTime time_now);
  void writeYear(DateTime time_now);
  void writeDay(DateTime time_now);
  void writeWeekDay(DateTime time_now);
  void writeHour(DateTime time_now);
  void writeMinute(DateTime time_now);
  void writeSecond(DateTime time_now);
  void writeTemp();
  void setAvgTemp();
};
#endif
