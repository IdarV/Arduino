#include "LedControl.h"
#include <binary.h>

LedControl lc = LedControl(12, 11, 10, 1);

// DATA_IN = 12
// CLK = 11
// LOADCS = 10
// NUMBER_OF_IC = 1

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

const int delay_time = 50;
const int TEXT_SIZE = 100;
int index = 0;

int text[TEXT_SIZE][8];
// dynamic allocation
int** ary = new int*[8];


void setup() {
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 15); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  // init array
  for(int i = 0; i < TEXT_SIZE; ++i)
      ary[i] = new int[8];
}





void scroll(){
  int i, j, i_i, trip_index;
  int trip = 0;
  for(i_i = 0; i_i < index; i_i++){
  for (i = 0; i <= 7; i++) {
    trip++;
    trip_index = 0;

    for (j = 0; j <= 7; j++) {
      if (j + trip > 7) {
        lc.setRow(0, j, ary[i_i][trip_index++]);
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
        lc.setRow(0, j, ary[i_i][trip_index--]);
      } else {
        lc.setRow(0, j, empty);
      }

    } delay(delay_time);
  }
  trip = 0;
  }

  lc.clearDisplay(0);
}

void add(int nee[] ){
  ary[index++] =nee;
}

void loop() {
  add(a);
  add(y);
  add(y);
  add(space);
//  scroll(a);
//  scroll(y);
//  scroll(y);
  scroll();
  lc.clearDisplay(0);
}



