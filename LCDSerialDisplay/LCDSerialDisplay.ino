/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN     13
#define light_pin A2

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // set the LCD address to 0x38

int spaces;
int forward;

void setup()
{
  pinMode ( BACKLIGHT_PIN, OUTPUT );
  pinMode(light_pin, INPUT);
  lcd.begin (16,2); 
  digitalWrite ( BACKLIGHT_PIN, HIGH );
  spaces = 0;
  forward = 1;
  Serial.begin(9600);
}

void loop()
{
  // when characters arrive over the serial port...
//  if (Serial.available()) 
//  {
    // wait a bit for the entire message to arrive
    
    delay(200);
    int light = analogRead(light_pin);
    Serial.println(light);
    lcd.clear();
    int i = 0;
    if(light > 255){
      light = 255;
    }
    if(light < 0){
      light = 0;
    }
//    lcd.setCursor(0,1);
//    i = 0;
//    for(;i < light/100 * 2; i++){
//      lcd.write("M");
//    }
    // clear the screen
   // lcd.clear();
    // read all the available characters
//    while (Serial.available() > 0) 
//    {
//      // display each character to the LCD
//      lcd.write(Serial.read());
//    }
//  }
}
