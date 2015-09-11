/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
bool is_value_in_array(int val, const int *arr) {
  int i;
  for (i = 0; arr[i] != -1; i++) {
    if(i > 5){
      Serial.print("WTF");
      delay(10000);
    }
    if (arr[i] == val)
      return true;
    }
  return false;
}

void light_up(const int *head) {
  for (int i = 7; i <= 13; i++) {
    if (is_value_in_array(i, head)) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital output pins
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, INPUT);
}
const int DIE_NONE[] = {-1};
const int DIE_ONE[] = {7, -1};
const int DIE_TWO[] = {11, 9, -1};
const int DIE_THREE[] = {12, 8, 7, -1};
const int DIE_FOUR[] = {12, 11, 9, 8, -1};
const int DIE_FIVE[] = {12, 11, 9, 8, 7, -1};
const int DIE_SIX[] = {13, 12, 11, 10, 9, 8, -1};
int buttonState = 0;
const int buttonPin = 4; 


// the loop function runs over and over again forever
void loop() {
//  light_up(DIE_ONE);
//  delay(1000);
//  light_up(DIE_TWO);
//  delay(1000);
//  light_up(DIE_THREE);
//  delay(1000);
//  light_up(DIE_FOUR);
//  delay(1000);
//  light_up(DIE_FIVE);
//  delay(1000);
//  light_up(DIE_SIX);
//  delay(1000);
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    light_up(DIE_THREE);
    delay(1000);
    light_up(DIE_NONE);
  }
}


