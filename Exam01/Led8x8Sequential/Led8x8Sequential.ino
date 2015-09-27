#include "LedControl.h"
LedControl lc = LedControl(2, 4, 3, 1);
int col = 0;
int row = 0;

void setup() {
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,8);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}

void loop() {
  // put your main code here, to run repeatedly:
  if(col == 8){
    col = 0;
    if(row < 7){
      row++;
    } else{
      row = 0;
    }
  } 

  lc.setLed(0,col,row,true); // turns on LED at col, row

  col++;
  
  delay(100);
  lc.clearDisplay(0);// clear screen
}
