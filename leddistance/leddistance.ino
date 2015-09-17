/*
HC-SR04 for Arduino
*/

/*
Reads distance from the distance thingy that looks like a speaker,
and lights up three lights depending on distance
*/

const int TriggerPin = 8;      //Trig pin
const int EchoPin = 9;         //Echo pin
const int ledGreen = 10;
const int ledYellow = 11;
const int ledRed = 6;
long Duration = 0;

int brightnessGreen = 0;
int brightnessYellow = 0;
int brightnessRed = 0;

void setup(){
  pinMode(TriggerPin,OUTPUT);  // Trigger is an output pin
  pinMode(EchoPin,INPUT);      // Echo is an input pin
  pinMode(ledGreen, OUTPUT);       // Green led
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  Serial.begin(9600);          // Serial Output
}

void loop(){ 
  digitalWrite(TriggerPin, LOW);                   
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);          // Trigger pin to HIGH
  delayMicroseconds(10);                   // 10us high 
  digitalWrite(TriggerPin, LOW);           // Trigger pin to HIGH
  Duration = pulseIn(EchoPin,HIGH);        // Waits for the echo pin to get high & returns the Duration in microseconds
  long Distance_mm = Distance(Duration);   // Use function to calculate the distance
  Serial.print("Distance = ");             // Output to serial
  brightnessRed = 0;
  brightnessYellow = 0;
  brightnessGreen = 0;
  if(Distance_mm < 255 && Distance_mm > 0){
    brightnessGreen = Distance_mm;
  } else if(Distance_mm < 510 && Distance_mm >= 255){
    brightnessYellow = Distance_mm - 255;
  } else if(Distance_mm >= 510) {
    if(Distance_mm > 715){
      brightnessRed = 255;
    } else{
      brightnessRed = Distance_mm - 510;
    }
  }
  Serial.print(Distance_mm);
  Serial.println(" mm");
  analogWrite(ledGreen, brightnessGreen);
  analogWrite(ledYellow, brightnessYellow);
  analogWrite(ledRed, brightnessRed);
  delay(30);                             // Wait to do next measurement
}

long Distance(long time)
{
    // Calculates the Distance in mm
    // ((time)*(Speed of sound))/ toward and backward of object) * 10
    long DistanceCalc = ((time /2.9) / 2);     // Actual calculation in mm
    return DistanceCalc;                    // return calculated value
}
