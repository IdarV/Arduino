/*
  Dice
  Creates a dice face with the press of a button
  
  by Idar Vassdal
 */

// Initialize die faces
const int DIE_NONE[] = {-1}; // NO LIGHTS
const int DIE_ONE[] = {7, -1}; 
const int DIE_TWO[] = {11, 9, -1};
const int DIE_THREE[] = {12, 8, 7, -1};
const int DIE_FOUR[] = {12, 11, 9, 8, -1};
const int DIE_FIVE[] = {12, 11, 9, 8, 7, -1};
const int DIE_SIX[] = {13, 12, 11, 10, 9, 8, -1};

// Initialize button
int buttonState = 0;
const int buttonPin = 4;

bool is_value_in_array(int val, const int *arr) {
  int i;
  for (i = 0; arr[i] != -1; i++) {
    if (arr[i] == val)
      return true;
    }
  return false;
}

void light_up(const int *head) {
  for (int i = 7; i <= 13; i++) {
    if (is_value_in_array(i, head)) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}

void play_animation_count(){
  const int *dices[7] = {DIE_ONE, DIE_TWO, DIE_THREE, DIE_FOUR, DIE_FIVE, DIE_SIX, DIE_NONE};
  int array_of_dies_size = 7;
  for(int i = 0; i < array_of_dies_size; i++){
    light_up(dices[i]);
    delay(200);
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
} 

// the loop function runs over and over again forever
void loop() {
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    int die_face_numb = 1 + (rand() % 6);
    
    play_animation_count();
    
    if(die_face_numb == 1){
      light_up(DIE_ONE);
    }
    if(die_face_numb == 2){
      light_up(DIE_TWO);
    }
    if(die_face_numb == 3){
      light_up(DIE_THREE);
    }
    if(die_face_numb == 4){
      light_up(DIE_FOUR);
    }
    if(die_face_numb == 5){
      light_up(DIE_FIVE);
    }
    if(die_face_numb == 6){
      light_up(DIE_SIX);
    }
  }
}


