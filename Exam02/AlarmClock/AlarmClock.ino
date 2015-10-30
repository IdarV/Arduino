#include "ClockMaster.h"
#include "Alarm.h"
#include <Wire.h>
#include "RTClib.h"
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

Alarm alarm;

// PS2
int xPin = A1;
int yPin = A0;
int buttonPin = 7;
int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

void setup(){
  clockSetup(&alarm);

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP);
  // For versions prior to Arduino 1.0.1
  // pinMode(buttonPin, INPUT);
  // digitalWrite(buttonPin, HIGH);
}

void setNewAlarm(){
  while(buttonState == 0){
    delay(10);
    buttonState = digitalRead(buttonPin);
  }
  delay(300);
  Serial.println("setNewAlarm()");
  int exitButtonPressed = 0;
  DateTime time_now = getTime();
  DateTime displayTime;
  int timeArray[3] = {0,0,0};

  int currentIndex = 0;

  while(exitButtonPressed == 0){
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    buttonState = digitalRead(buttonPin);

    int lastX = xPosition;
    int lastY = yPosition;

    // if button is pressed, exit alarm setting
    if(buttonState == 0){
      exitButtonPressed = 1;
      alarm.setAlarmButtonState(0);
      alarm.setAlarm(displayTime);
      resetDisplayTime(getTime());
    } else{
      if(xPosition == 0){
        // If move right, check if can move right
        if(currentIndex < 2){
          currentIndex++;
        }
      } else if(xPosition == 1021){
        // If move left, check if can move left
        if(currentIndex > 0){
          currentIndex--;
        }
      } else if(yPosition == 0){
        timeArray[currentIndex] = timeArray[currentIndex] + 1;
      } else if(yPosition == 1021){
        timeArray[currentIndex] = timeArray[currentIndex] - 1;
      }


      Serial.print("currentIndex: ");
      Serial.print(currentIndex);
      Serial.print(", array: ");
      Serial.print(timeArray[0]);
      Serial.print(", ");
      Serial.print(timeArray[1]);
      Serial.print(", ");
      Serial.print(timeArray[2]);
      Serial.print(", X: ");
      Serial.print(xPosition);
      Serial.print(" | Y: ");
      Serial.print(yPosition);
      Serial.print(" | Button: ");
      Serial.println(buttonState);

      displayTime = time_now + TimeSpan(0, timeArray[0], timeArray[1], timeArray[2]);//timeDifference;

      resetDisplayTime(displayTime);
    }
  }
}

void loop() {

  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(buttonPin);

  if(buttonState == 0){
    setNewAlarm();
  }

  delay(100); // add some delay between reads
  // Get time
  DateTime time_now = getTime();
  // Update display
  updateDisplayTime(time_now);
  // Wait for next second from clock;
  waitForNextSecond(time_now, &alarm);
}
