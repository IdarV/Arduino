#include "LedControl.h"
#include <binary.h>

LedControl lc = LedControl(12, 11, 10, 1);

// DATA_IN = 12
// CLK = 11
// LOADCS = 10
// NUMBER_OF_IC = 1

int empty = B0000000;

int a[] = {
  B11111110,
  B11111111,
  B11111111,
  B00110011,
  B00110011,
  B11111111,
  B11111111,
  B11111110,
  B00000000,
  B00000000
};

int e[] {
  B11111111,
  B11111111,
  B11111111,
  B11011011,
  B11011011,
  B11011011,
  B11000011,
  B11000011,
  B00000000,
  B00000000

};

int f[] {
  B11111111,
  B11111111,
  B11111111,
  B00011011,
  B00011011,
  B00011011,
  B00000011,
  B00000011,
  B00000000,
  B00000000
};

int l[] {
  B01111111,
  B11111111,
  B11111111,
  B11100000,
  B11100000,
  B11100000,
  B11100000,
  B01100000,
  B00000000,
  B00000000
};

int m[] {
  B11111110,
  B11111111,
  B11111110,
  B00001100,
  B00001100,
  B11111110,
  B11111111,
  B11111110,
  B00000000,
  B00000000
};

int o[] {
  B00111100,
  B01111110,
  B11111111,
  B11100111,
  B11100111,
  B11111111,
  B01111110,
  B00111100,
  B00000000,
  B00000000
};

int y[] = {
  B00000111,
  B00001111,
  B00011111,
  B11111000,
  B11111000,
  B00011111,
  B00001111,
  B00000111,
  B00000000,
  B00000000
};

int space[] = {
  B00000000,
  B00000000,
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

//int text[TEXT_SIZE][8];
// dynamic allocation
int** ary = new int*[10];


void setup() {
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 15); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  // init array
  for (int i = 0; i < TEXT_SIZE; ++i) {
    ary[i] = new int[8];
  }
  Serial.begin(9600);
  add(space);
  add(a);
  add(e);
  add(space);
}





void scroll() {
  int  j, i_i;
  Serial.println(index * 10);
  for (i_i = 0; i_i < (index * 9) - 10; i_i++) {
    for (j = 7; j >= 0; j--) {
      int this_a = 0;
      int this_b = i_i + j;
      while (this_b > 9) {
        this_b -= 9;
        this_a++;
      }
      lc.setRow(0, j, ary[this_a][this_b]);

    } delay(delay_time);

  }

  lc.clearDisplay(0);
}

void add(int character[] ) {
  ary[index++] = character;
}

void add_if_found(char c) {
  switch (c) {
    case 'a':
    case 'A':
      add(a);
      break;
    case 'e':
    case 'E':
      add(e);
      break;
    case 'f':
    case 'F':
      add(f);
      break;
    case 'l':
    case 'L':
      add(l);
      break;
    case 'm':
    case 'M':
      add(m);
      break;
    case 'o':
    case 'O':
      add(o);
      break;
    case 'y':
    case 'Y':
      add(y);
      break;
    case ' ':
      add(space);
      break;
    default:
      break;
  }
}

void read_from_serial() {
  index = 0;
  add(space);
  while (Serial.available() > 0) {
    add_if_found(Serial.read());
  }
  add(space);

}
int i = 0;

void loop() {
  if (Serial.available() > 0) {
    read_from_serial();
  } else {
    delay(1000);
  }
  scroll();
}



