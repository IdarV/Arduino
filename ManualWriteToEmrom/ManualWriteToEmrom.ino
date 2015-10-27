#include <Wire.h>

void setup() {
  // WRITE:
  Serial.begin(9600);
  Wire.begin();
  delay(100);
  Wire.beginTransmission(0x50); // EMrom
  Wire.write(0x0);
  Wire.write(0x0);
  Wire.write("1234567890098765432101234567890");
  byte error = Wire.endTransmission();
  Serial.print("Writing first status:");
  Serial.println(error);

  delay(100);

  Wire.beginTransmission(0x50);
  Wire.write(0x2);
  Wire.write(0x1);
  Wire.write("abcdefghijklmnopqrstuvwxyz");
  error = Wire.endTransmission();
  Serial.print("Writing second status:");
  Serial.println(error);

  delay(100);

  // READ:
  Wire.beginTransmission(0x50);
  Wire.write(0x0);
  Wire.write(0x0);
  Wire.endTransmission();
  Wire.requestFrom(0x50, 30);

  byte returnedByte;
  while (Wire.available()) {
    returnedByte = Wire.read();
    Serial.write(returnedByte);
  }

  Serial.println();

  Wire.beginTransmission(0x50);
  Wire.write(0x2);
  Wire.write(0x1);
  Wire.endTransmission();
  Wire.requestFrom(0x50, 30);
  while (Wire.available()) {

    returnedByte = Wire.read();
    if (returnedByte != 255) {
      Serial.write(returnedByte);
    }
  }
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

}
