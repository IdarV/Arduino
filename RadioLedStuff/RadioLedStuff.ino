#include <rf24HQ.h>
#include <SPI.h>

int ledRedPin = 7;
int ledGreenPin = 6;
int btnOnePin = 4;
int btnTwoPin = 3;

rf24 rf(8,9,100,RF24_MAX_SIZE);

void setup(){
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(btnOnePin, INPUT);
  pinMode(btnTwoPin, INPUT);
  Serial.begin(115200);


  rf.begin(&Serial);
  rf.setTxAddr("idarv");
  rf.setRxAddr(1, "kimmm");
  rf.setRxAddr(2, "marti");
  rf.dumpRegisters();

}

void loop(){
  int btnOneState = digitalRead(btnOnePin);
  int btnTwoState = digitalRead(btnTwoPin);

  if(btnOneState){
    char data[RF24_MAX_SIZE] = "HEI JEG ER IDAR";
    rf.send(data, sizeof(data));
  }

  if(btnTwoState){
    char data[RF24_MAX_SIZE] = "HEI JEG ER IDAR 2";
    rf.send(data, sizeof(data));
  }

  char datain[RF24_MAX_SIZE];
  if (rf.available()) {
	    rf.read(datain, sizeof(datain));
      Serial.print("Gut  message: ");
      Serial.println(datain);
      digitalWrite(ledGreenPin, HIGH);
	} else{

    digitalWrite(ledGreenPin, LOW);
  }

  delay(50);

}
