#include "ClockMaster.h"
#include "Alarm.h"
#include <Wire.h>
#include "RTClib.h"
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

Alarm alarm;

void setup(){
  clockSetup(&alarm);
}

void loop() {
  // Get time
  DateTime time_now = getTime();
  // Update display
  updateDisplayTime(time_now);
  // Wait for next second from clock;
  waitForNextSecond(time_now, &alarm);
}
