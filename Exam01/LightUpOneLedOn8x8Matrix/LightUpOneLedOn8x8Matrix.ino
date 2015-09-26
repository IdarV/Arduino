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
