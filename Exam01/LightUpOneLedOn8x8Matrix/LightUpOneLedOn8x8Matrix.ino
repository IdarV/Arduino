/*
* This script will light up one led on a 8x8 matrix.
* Both cables should be added with a 220 ohm resistor.
* Connect pin 8 to a col, and pin 7 to a row.
* Follow the matrix-pin-sheet in this project.
*/

const int col = 8;
const int row = 7;
void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(row, HIGH);
  digitalWrite(col, LOW);
  delay(10000);
}
