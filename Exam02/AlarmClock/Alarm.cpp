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
}

// void Alarm::setNewAlarm(ClockMaster *cm, int xPin, int yPin){
//   int buttonState = 0;
//   while(buttonState == 0){
//     delay(10);
//     buttonState = digitalRead(buttonPin);
//   }
//   delay(300);
//   int exitButtonPressed = 0;
//   DateTime time_now = cm->getTime();
//   DateTime displayTime;
//   int timeArray[3] = {0,0,0};
//   bool updateGUI = true;
//   int currentIndex = 0;
//
//   while(exitButtonPressed == 0){
//     xPosition = analogRead(xPin);
//     yPosition = analogRead(yPin);
//     buttonState = digitalRead(buttonPin);
//
//     // if button is pressed, exit alarm setting
//     if(buttonState == 0){
//       exitButtonPressed = 1;
//       setAlarmButtonState(0);
//       setAlarm(displayTime);
//       cm->resetDisplayTime(cm->getTime(), -1);
//     } else{
//       if(xPosition < 10){
//         // If move right, check if can move right and do so if we can
//         if(currentIndex < 2){
//           currentIndex++;
//           updateGUI = true;
//         }
//       } else if(xPosition > 1000){
//         // If move left, check if can move left and do so if we can
//         if(currentIndex > 0){
//           currentIndex--;
//           updateGUI = true;
//         }
//       } else if(yPosition == 0){
//         timeArray[currentIndex] = timeArray[currentIndex] + 1;
//         updateGUI = true;
//       } else if(yPosition == 1021){
//         timeArray[currentIndex] = timeArray[currentIndex] - 1;
//         updateGUI = true;
//       }
//
//       displayTime = time_now + TimeSpan(0, timeArray[0], timeArray[1], timeArray[2]);//timeDifference;
//
//       if(updateGUI){
//         cm->resetDisplayTime(displayTime, currentIndex);
//         updateGUI = false;
//       }
//     }
//   }
// }
