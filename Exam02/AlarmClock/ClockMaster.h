#ifndef ClockMasterHeadFile
#define ClockMasterHeadFile
#include <Wire.h>
#include "RTClib.h"

void clockSetup();
DateTime getTime();
void updateDisplayTime(DateTime time_now);
void waitForNextSecond(DateTime time_now);

#endif
