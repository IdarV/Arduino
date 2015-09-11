/*
  Dice
  Creates a dice face with the press of a button

  by Idar Vassdal
 */

// Initialize die faces
const int DIE_NONE[] = { -1}; // NO LIGHTS
const int DIE_ONE[] = {7, -1};
const int DIE_TWO[] = {11, 9, -1};
const int DIE_THREE[] = {12, 8, 7, -1};
const int DIE_FOUR[] = {12, 11, 9, 8, -1};
const int DIE_FIVE[] = {12, 11, 9, 8, 7, -1};
const int DIE_SIX[] = {13, 12, 11, 10, 9, 8, -1};
const int DIE_ALL[] = {13, 12, 11, 10, 9, 8, 7, -1};

// Initialize button
int buttonState = 0;
const int buttonPin = 4;

// .include?
bool is_value_in_array(int val, const int *arr) {
  int i;
  for (i = 0; arr[i] != -1; i++) {
    if (arr[i] == val)
      return true;
  }
  return false;
}

// Lights up a die head on the leds
void light_up(const int *head) {
  for (int i = 7; i <= 13; i++) {
    if (is_value_in_array(i, head)) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}

// Plays counting animation
void play_animation_count() {
  const int *dices[7] = {DIE_ONE, DIE_TWO, DIE_THREE, DIE_FOUR, DIE_FIVE, DIE_SIX, DIE_NONE};
  int array_of_dies_size = 7;
  for (int i = 0; i < array_of_dies_size; i++) {
    light_up(dices[i]);
    delay(125);
  }
  delay(50);
}

// plays spinning animation
void play_animation_spin() {
  int roundtrip[][6] = {{12, -1}, {10, -1}, {9, -1}, {8, -1}, {13, -1}, {11, -1}};
  for (int i = 0; i < 6; i++) {
    light_up(roundtrip[i]);
    delay(50);
  }
}

// shows dice for #input
void show_dice(int i){
  switch (i) {
      case 1:
        light_up(DIE_ONE);
        break;
      case 2:
        light_up(DIE_TWO);
        break;
      case 3:
        light_up(DIE_THREE);
        break;
      case 4:
        light_up(DIE_FOUR);
        break;
      case 5:
        light_up(DIE_FIVE);
        break;
      case 6:
        light_up(DIE_SIX);
        break;
      default:
        break;
    }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital output pins
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, INPUT);

  // seeding the random fuction with static noise from all ports
  randomSeed(analogRead(0) * analogRead(1) * analogRead(2) * analogRead(3) * analogRead(4) * analogRead(5));
}

// the loop function runs over and over again forever
void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    int die_face = random(1, 6);

    play_animation_spin();
    play_animation_count();

    show_dice(die_face);
  }
}


