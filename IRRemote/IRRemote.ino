
////////////////////////////////////////////////
// This demo code reads the codes from an IR remote
// and displays them on a 2-line LCD
//
// This code may be freely used and copied.
//
// Gareth Davies - June 2012
//
////////////////////////////////////////////////

#define IR_IN  6  // Use ditial pin 8 for input from receiver
int Pulse_Width=0;
int ir_code=0x00;
char  adrL_code=0x00;
char  adrH_code=0x00;
char lastCode; // saves the last pressed button

void timer1_init(void)
{
  TCCR1A = 0X00;
  TCCR1B = 0X05;
  TCCR1C = 0X00;
  TCNT1 = 0X00;
  TIMSK1 = 0X00;
}

char logic_value()
{
  TCNT1 = 0X00;
  while(!(digitalRead(IR_IN)));
  Pulse_Width=TCNT1;
  TCNT1=0;
  if(Pulse_Width>=7&&Pulse_Width<=10)
  {
    while(digitalRead(IR_IN));
    Pulse_Width=TCNT1;
    TCNT1=0;
    if(Pulse_Width>=7&&Pulse_Width<=10) //560us
      return 0;
    else if(Pulse_Width>=25&&Pulse_Width<=27) //1.7ms
      return 1;
  }
  return -1;
}

void pulse_deal()
{
  int i;
  int j;
  ir_code=0x00;
  adrL_code=0x00;
  adrH_code=0x00;

  for(i = 0 ; i < 16; i++)
  {
    if(logic_value() == 1)
        ir_code |= (1<<i);
  }
  for(i = 0 ; i < 8; i++)
  {
    if(logic_value() == 1)
      adrL_code |= (1<<i);
  }
  for(j = 0 ; j < 8; j++)
  {
    if(logic_value() == 1)
        adrH_code |= (1<<j);
  }
}

void remote_decode(void)
{
  TCNT1=0X00;
  while(digitalRead(IR_IN))
  {
    if(TCNT1>=1563)
    {
      ir_code=0x00ff;
      adrL_code=0x00;
      adrH_code=0x00;
      return;
    }
  }
  TCNT1=0X00;
  while(!(digitalRead(IR_IN)));
  Pulse_Width=TCNT1;
  TCNT1=0;
  if(Pulse_Width>=140&&Pulse_Width<=141) //9ms
  {
    while(digitalRead(IR_IN));
    Pulse_Width=TCNT1;
    TCNT1=0;
    if(Pulse_Width>=68&&Pulse_Width<=72) //4.5ms
    {
      pulse_deal();
      return;
    }
    else if(Pulse_Width>=34&&Pulse_Width<=36) //2.25ms
    {
      while(!(digitalRead(IR_IN)));
      Pulse_Width=TCNT1;
      TCNT1=0;
      if(Pulse_Width>=7&&Pulse_Width<=10) //560us
      {
        return;
      }
    }
  }
}

void setup()
{
  unsigned char i;
  pinMode(IR_IN,INPUT);
  Serial.begin(9600);

  timer1_init();
  delay(100);
}

void loop()
{
  remote_decode();
  if( adrL_code != lastCode ){
    lastCode = adrL_code;
    if( adrL_code == 0 ){
      Serial.print("keyUp  :");
    } else {
      Serial.print("keyDown:");
    }
    Serial.println(adrL_code,HEX);
  }
}
