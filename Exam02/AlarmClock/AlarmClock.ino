#include "Alarm.h"
#include "ClockMaster.h"
#include <Wire.h>
#include "RTClib.h"
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <DHT.h>

Alarm alarm;
ClockMaster cm;

// PS2-joystick settings
int xPin = A1;
int yPin = A0;
int buttonPin = 7;
int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

void setup(){
  cm.clockSetup(&alarm);

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP);
}

// Method for running set-the-alarm interface
void setNewAlarm(){
  // Wait for button to be released
  while(buttonState == 0){
    delay(10);
    buttonState = digitalRead(buttonPin);
  }

  delay(300);
  int exitButtonPressed = 0;
  DateTime time_now = cm.getTime(); // Time when first entering alarm
  DateTime displayTime; // Time to display
  int timeArray[3] = {0,0,0}; // Added HH/MM/SS
  bool updateGUI = true; // Only update GUI when something has changed
  int currentIndex = 0;

  // While PS2 button is not pressed again
  while(exitButtonPressed == 0){
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    buttonState = digitalRead(buttonPin);

    // if button is pressed, exit the set-the-alarm interface
    if(buttonState == 0){
      // Reset time, set alarm
      exitButtonPressed = 1;
      alarm.setAlarmButtonState(0);
      alarm.setAlarm(displayTime);
      cm.resetDisplayTime(cm.getTime(), -1);
    } else{
      // If move right, check if can move right and do so if we can
      if(xPosition < 10){
        if(currentIndex < 2){
          currentIndex++;
          updateGUI = true;
        }
        // If move left, check if can move left and do so if we can
      } else if(xPosition > 1000){
        if(currentIndex > 0){
          currentIndex--;
          updateGUI = true;
        }
      } else if(yPosition < 10){
        timeArray[currentIndex] = timeArray[currentIndex] + 1;
        updateGUI = true;
      } else if(yPosition > 1000){
        timeArray[currentIndex] = timeArray[currentIndex] - 1;
        updateGUI = true;
      }

      // Displat the original time, plus the added HH/MM/SS
      displayTime = time_now + TimeSpan(0, timeArray[0], timeArray[1], timeArray[2]);

      // Update GUI only if we have changed something
      if(updateGUI){
        cm.resetDisplayTime(displayTime, currentIndex);
        updateGUI = false;
      }
    }
  }
}

void loop() {
  // Check if the joystick is pressed
  buttonState = digitalRead(buttonPin);

  // If the joystick is pressed, enter alarm-settings
  if(buttonState == 0){
    setNewAlarm();
  }

  // Some delay between reads
  delay(100);
  // Get time now
  DateTime time_now = cm.getTime();
  // Update display
  cm.updateDisplayTime(time_now);
  // Wait for next second from clock
  cm.waitForNextSecond(time_now, &alarm);
}
