#include "ClockMaster.h"
#include <Wire.h>
#include "RTClib.h"
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

void setup(){
  clockSetup();
}

void loop() {
  // Get time
  DateTime time_now = getTime();
  // Update display
  updateDisplayTime(time_now);
  // Wait for next second from clock;
  waitForNextSecond(time_now);
}
