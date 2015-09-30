#include "LedControl.h"
#include <binary.h>

LedControl lc = LedControl(12, 11, 10, 1);

// Delay between each update
const int delay_time = 50;
// Size of allocated string
const int TEXT_SIZE = 100;
int index = 0;

// dynamic allocation
int** print_string = new int*[10];

int a[] {
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

int b[] {
  B11111111,
  B11111111,
  B11111111,
  B11011011,
  B11011011,
  B11111111,
  B11111111,
  B01100110,
  B00000000,
  B00000000
};

int c[] {
  B01111110,
  B11111111,
  B11111111,
  B11000011,
  B11000011,
  B11100111,
  B11100111,
  B01100110,
  B00000000,
  B00000000
};

int d[] {
  B11111111,
  B11111111,
  B11111111,
  B11000011,
  B11000011,
  B11111111,
  B11111111,
  B01111110,
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
  B11000010,
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

int g[] {
  B01111110,
  B11111111,
  B11111111,
  B11000011,
  B11010011,
  B11110111,
  B11110111,
  B01110110,
  B00000000,
  B00000000
};

int h[] {
  B11111111,
  B11111111,
  B11111111,
  B00011000,
  B00011000,
  B11111111,
  B11111111,
  B11111111,
  B00000000,
  B00000000
};

int i[] {
  B00000000,
  B00000000,
  B00000000,
  B11111111,
  B11111111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

int j[] {
  B11000000,
  B11000000,
  B11000000,
  B11111111,
  B11111111,
  B01111111,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

int k[] {
  B11111111,
  B11111111,
  B11111111,
  B00011000,
  B00111100,
  B01111110,
  B11100111,
  B11000011,
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

int n[] {
  B11111111,
  B11111111,
  B11111111,
  B00111110,
  B01111100,
  B11111111,
  B11111111,
  B11111111,
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

int p[] {
  B11111111,
  B11111111,
  B11111111,
  B00011011,
  B00011011,
  B00011111,
  B00011111,
  B00001110,
  B00000000,
  B00000000
};

int q[] {
  B01111110,
  B11111111,
  B11111111,
  B11000011,
  B10100011,
  B01101111,
  B11011111,
  B10111110,
  B00000000,
  B00000000
};

int r[] {
  B11111111,
  B11111111,
  B11111111,
  B00011011,
  B00011011,
  B11111111,
  B11111111,
  B11101110,
  B00000000,
  B00000000
};

int s[] {
  B01001110,
  B11011111,
  B11011111,
  B11011011,
  B11011011,
  B11110011,
  B11110011,
  B01110010,
  B00000000,
  B00000000
};

int t[] {
  B00000011,
  B00000011,
  B11111111,
  B11111111,
  B11111111,
  B00000011,
  B00000011,
  B00000011,
  B00000000,
  B00000000
};

int u[] {
  B01111111,
  B11111111,
  B11111111,
  B11000000,
  B11000000,
  B11111111,
  B11111111,
  B01111111,
  B00000000,
  B00000000
};

int v[] {
  B00111111,
  B01111111,
  B11111111,
  B11000000,
  B11000000,
  B11111111,
  B01111111,
  B00111111,
  B00000000,
  B00000000
};

int w[] {
  B11111111,
  B11111111,
  B11111111,
  B01110000,
  B00110000,
  B01110000,
  B11111111,
  B11111111,
  B00000000,
  B00000000
};

int x[] {
  B11000011,
  B11100111,
  B11111111,
  B00111100,
  B00111100,
  B11111111,
  B11100111,
  B11000011,
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

int z[] {
  B11100011,
  B11110011,
  B11110011,
  B11111011,
  B11011111,
  B11001111,
  B11001111,
  B11000111,
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

void setup() {
  // Standard LC setup
  lc.shutdown(0, false);
  lc.setIntensity(0, 15);
  lc.clearDisplay(0);

  // Add 'hello' as default message
  add(space);
  add(h);
  add(e);
  add(l);
  add(l);
  add(o);
  add(space);

  Serial.begin(9600);
}

void scroll() {
  int i, j;

  // For each singe row of the total rows of all the 
  // characters in the current print_string 
  // (each is 10 bytes long, _index_ is length of string)
  for (i = 0; i < (index * 10) - 10; i++) {
    // Seven times
    for (j = 7; j >= 0; j--) {
      // Print row of characters
      int this_a = 0;
      int this_b = i + j;
      while (this_b > 9) {
        // If end of current char, start printing next
        this_b -= 10;
        this_a++;
      }
      // Print current row to screen
      lc.setRow(0, j, print_string[this_a][this_b]);
    }
    // Add some delay
    delay(delay_time);
  }

  lc.clearDisplay(0);
}

// Adds a char to the string
void add(int character[] ) {
  print_string[index++] = character;
}

// Add a letter if it exists
void add_if_found(char ch) {
  switch (ch) {
    case 'a':
    case 'A':
      add(a);
      break;
    case 'b':
    case 'B':
      add(b);
      break;
    case 'c':
    case 'C':
      add(c);
      break;
    case 'd':
    case 'D':
      add(d);
      break;
    case 'e':
    case 'E':
      add(e);
      break;
    case 'f':
    case 'F':
      add(f);
      break;
    case 'g':
    case 'G':
      add(g);
      break;
    case 'h':
    case 'H':
      add(h);
      break;
    case 'i':
    case 'I':
      add(i);
      break;
    case 'j':
    case 'J':
      add(j);
      break;
    case 'k':
    case 'K':
      add(k);
      break;
    case 'l':
    case 'L':
      add(l);
      break;
    case 'm':
    case 'M':
      add(m);
      break;
    case 'n':
    case 'N':
      add(n);
      break;
    case 'o':
    case 'O':
      add(o);
      break;
    case 'p':
    case 'P':
      add(p);
      break;
    case 'q':
    case 'Q':
      add(q);
      break;
    case 'r':
    case 'R':
      add(r);
      break;
    case 's':
    case 'S':
      add(s);
      break;
    case 't':
    case 'T':
      add(t);
      break;
    case 'u':
    case 'U':
      add(u);
      break;
    case 'v':
    case 'V':
      add(v);
      break;
    case 'w':
    case 'W':
      add(w);
      break;
    case 'x':
    case 'X':
      add(x);
      break;
    case 'y':
    case 'Y':
      add(y);
      break;
    case 'z':
    case 'Z':
      add(z);
      break;
    case ' ':
      add(space);
      break;
    default:
      break;
  }
}

// Read from the serial
void read_from_serial_if_new_input() {
  if (Serial.available() > 0) {
    // reset index and start adding numbes
    index = 0;
    add(space);
    while (Serial.available() > 0) {
      add_if_found(Serial.read());
    }
    add(space);
  }
  else {
    delay(1000);
  }
}


void loop() {
  // Read from serial if it has new input
  read_from_serial_if_new_input();
  // scroll through text
  scroll();
}
