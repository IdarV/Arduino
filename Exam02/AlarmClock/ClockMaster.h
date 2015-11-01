#ifndef ClockMasterHeadFile
#define ClockMasterHeadFile
#include <Wire.h>
#include "Alarm.h"
#include "RTClib.h"

void clockSetup(Alarm *alarm);
DateTime getTime();
void updateDisplayTime(DateTime time_now);
void waitForNextSecond(DateTime time_now, Alarm *alarm);
void resetDisplayTime(DateTime newTime, int currentXPos);

#endif
