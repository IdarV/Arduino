/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN     13

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // set the LCD address to 0x38

int spaces;
int forward;

void setup()
{
  pinMode ( BACKLIGHT_PIN, OUTPUT );
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
    lcd.clear();
    int i = 0;
    for(;i < spaces; i++){
      lcd.write(" ");
    }
    lcd.write("?");
    // clear the screen
   // lcd.clear();

    if(spaces == 14){
      forward = 0;
    }
    if(spaces == 0){
      forward = 1;
    }
    if(forward){
      spaces++;
    } else{
      spaces--;
    }
    // read all the available characters
//    while (Serial.available() > 0) 
//    {
//      // display each character to the LCD
//      lcd.write(Serial.read());
//    }
//  }
}
