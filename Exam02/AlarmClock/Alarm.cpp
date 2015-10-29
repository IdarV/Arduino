#include <Wire.h>
#include "RTClib.h"
#include "Alarm.h"
// Declare Real Time Clock

void Alarm::setAlarm(DateTime date){
  _alarmMillis = date;
}

void Alarm::cancelAlarm(){
  _alarmMillis = 0;
}

DateTime Alarm::getAlarm(){
  return _alarmMillis;
}

bool Alarm::ring(){
  tone(2, _alarmTone, 10);
}

void Alarm::setAlarmButtonState(int state){
  _alarmButtonPressed = state;
}

bool Alarm::alarmState(){
    return _alarmButtonPressed;
}

bool Alarm::alarmButtonIsPressed(){
  return HIGH == digitalRead(_alarmButtonPin);
}

void Alarm::initAlarm(DateTime time_now){
  _alarmTonePin = 2;
  _alarmTone;
  _alarmButtonPin = 4;
  _alarmButtonPressed = 0;
  _alarmTone = 1480;
  _alarmMillis = DateTime(time_now + TimeSpan(0, 0, 0, 10));

  pinMode(_alarmTonePin, OUTPUT);
  pinMode(_alarmButtonPin, OUTPUT);
}
