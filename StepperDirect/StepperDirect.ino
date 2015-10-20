// This Arduino example demonstrates bidirectional operation of a 
// 28BYJ-48, using a ULN2003 interface board to drive the stepper.
// The 28BYJ-48 motor is a 4-phase, 8-beat motor, geared down by
// a factor of 68. One bipolar winding is on motor pins 1 & 3 and
// the other on motor pins 2 & 4. The step angle is 5.625/64 and the 
// operating Frequency is 100pps. Current draw is 92mA. 
////////////////////////////////////////////////

//declare variables for the motor pins
int motorPin1 = 8;    // Arduino pin 8 -> IN1
int motorPin3 = 9;    // Arduino pin 9 -> IN3
int motorPin2 = 10;    // Arduino pin 10 -> IN2
int motorPin4 = 11;    // Arduino pin 11 -> IN4

int motorSpeed = 3000;  //variable to set stepper speed
int count = 0;          // count of steps made
int countsperrev = 528; // number of steps per full revolution
const int len = 4;
uint8_t lookup[len] = {
  B01100, B00110, B00011, B01001};


//////////////////////////////////////////////////////////////////////////////
void setup() {
  //declare the motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);
}

//////////////////////////////////////////////////////////////////////////////
void loop(){
  if(count < countsperrev )
    clockwise();
  else if (count == countsperrev * 2)
    count = 0;
  else
    anticlockwise();
  count++;
}

//////////////////////////////////////////////////////////////////////////////
//set pins to ULN2003 high in sequence from 1 to 4
//delay "motorSpeed" between each pin setting (to determine speed)
void anticlockwise()
{
  for(int i = 0; i < len; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise()
{
  for(int i = (len-1); i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void setOutput(uint8_t out)
{
  Serial.print("setOutput: ");
  Serial.println(out % len);
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
//  delay(500);
}

