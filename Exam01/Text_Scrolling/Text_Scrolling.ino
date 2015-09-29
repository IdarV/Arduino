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

int l[]{
  B01111111,
  B11111111,
  B11111111,
  B11100000,
  B11100000,
  B11100000,
  B11100000,
  B01100000
};

int m[]{
  B11111110,
  B11111111,
  B11111110,
  B00001100,
  B00001100,
  B11111110,
  B11111111,
  B11111110
};

int o[]{
  B00111100,
  B01111110,
  B11111111,
  B11100111,
  B11100111,
  B11111111,
  B01111110,
  B00111100
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

//void create_string(char *str);

int text[TEXT_SIZE][8];
// dynamic allocation
int** ary = new int*[8];


void setup() {
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 15); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  // init array
  for(int i = 0; i < TEXT_SIZE; ++i){
      ary[i] = new int[8];
  }
  Serial.begin(9600);
//  create_string("AYY LMAO\0");
  
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

void add(int character[] ){
  ary[index++] = character;
}

void add_if_found(char c){
  switch(c){
    case 'a':
    case 'A':
      add(a);
      break;
    case 'l':
    case 'L':
      add(l);
      break;
    case 'o':
    case 'O':
      add(o);
      break;
    default:
      break;
  }
}

void read_from_serial(){
  int index = 0;
  while(Serial.available() > 0){
    add_if_found(Serial.read());
  }
}
int i = 0;

void loop() {
  if(Serial.available() > 0){
    read_from_serial();
  } else{
    delay(1000);
  }
//  add(a);
//  add(y);
//  add(y);
//  add(l);
//  add(m);
//  add(a);
//  add(o);
//  add(space);
  scroll();
  lc.clearDisplay(0);
}



