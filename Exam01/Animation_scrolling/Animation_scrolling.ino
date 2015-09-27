#include "LedControl.h"

LedControl lc = LedControl(2, 4, 3, 1); //idk how

typedef struct{
  int col;
  int row;
} Led;

void smiley();
void light_up(int col, int row) {
  lc.setLed(0, col - 1, row - 1, true);
}
void display(int fig[][2], int fig_size) {
  int col, row, i;
  for (i = 0; i <= fig_size; i++) {
    col = fig[i][0];
    row = fig[i][1];
    if (col > 0 && col < 9 && row > 0 && row < 9) {
      light_up(col, row);
    }
  }
}

void scroll_left(int fig[][2], int fig_size, int delay_ms) {
  int i, j = 0;
  for (int i = 0; i < fig_size; i++) {
    fig[i][0] = fig[i][0] + 8;
  }
  while (j < 16) {
    j++;
    for (int i = 0; i < fig_size; i++) {
      fig[i][0] = fig[i][0] - 1;
    }
    display(fig, fig_size);
    delay(100);
    lc.clearDisplay(0);// clear screen
  }
}


void setup() {
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 8); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}

void loop() {
  // put your main code here, to run repeatedly:
  int smiley_fig[10][2] = {
    {2, 3},
    {2, 4},
    {3, 7},
    {3, 2},
    {4, 2},
    {5, 2},
    {6, 2},
    {6, 7},
    {7, 3},
    {7, 3}
  };

  scroll_left(smiley_fig, 10, 100);
}

void smiley() {
  //display(smiley_fig, 10);
}



