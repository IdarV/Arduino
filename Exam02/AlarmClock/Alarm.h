#ifndef AlarmHeadFile
#define AlarmHeadFile
#include <Wire.h>
#include "RTClib.h"

class Alarm{
public:
  void setAlarm(DateTime date);
  void setAlarmButtonState(int state);
  bool alarmState();
  void cancelAlarm();
  DateTime getAlarm();
  bool ring();
  void initAlarm(DateTime time_now);
  bool alarmButtonIsPressed();

private:
  int xPosition = 0;
  int yPosition = 0;
  int buttonState = 0;
  int buttonPin = 7;
  int _alarmTonePin;
  int _alarmTone;
  int _alarmButtonPin;
  int _alarmButtonPressed;
  DateTime _alarmMillis;
};

#endif
