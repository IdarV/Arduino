#include "LedControl.h"
#include <binary.h>

LedControl lc = LedControl(12, 11, 10, 1);

// DATA_IN = 12
// CLK = 11
// LOADCS = 10
// NUMBER_OF_IC = 1

const int delay_time = 50;

void setup() {
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 15); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}



int empty = B0000000;

int a[8] = {
  B11111110,
  B11111111,
  B11111111,
  B00110011,
  B00110011,
  B11111111,
  B11111111,
  B11111110
};

int y[]= {
  B00000111,
  B00001111,
  B00011111,
  B11111000,
  B11111000,
  B00011111,
  B00001111,
  B00000111
};

int space[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

void scroll(int letter[]){
  int i, j, trip_index;
  int trip = 0;

  for (i = 0; i <= 7; i++) {
    trip++;
    trip_index = 0;

    for (j = 0; j <= 7; j++) {
      if (j + trip > 7) {
        lc.setRow(0, j, letter[trip_index++]);
      } else {
        lc.setRow(0, j, empty);
      }

    } delay(delay_time);
  }
  trip = 0;
  for (i = 0; i <= 7; i++) {
    trip++;
    trip_index = 7;

    for (j = 7; j >= 0; j--) {
      if (j + trip <= 7) {
        lc.setRow(0, j, letter[trip_index--]);
      } else {
        lc.setRow(0, j, empty);
      }

    } delay(delay_time);
  }

  lc.clearDisplay(0);
}
int text[100][8];


void loop() {
  scroll(a);
  scroll(y);
  scroll(y);
  scroll(space);
  lc.clearDisplay(0);
}



