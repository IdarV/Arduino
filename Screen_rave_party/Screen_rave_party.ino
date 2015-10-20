//************************//
//    Modify by WIDE.HK   //
//************************//
// X  Connected to A0
// Y  Connected to A1
// Z  Connected to A2

// MicroSD CS    Connected to D4
// MicroSD MISO  Connected to D12

// TFT+MicroSD !SCL  Connected to D13
// TFT+MicroSD !SDA  Connected to D11
// TFT          DC   Connected to D9
// TFT          RES  Connected to D8
// TFT          CS   Connected to D10

//************************//
//    Modify by WIDE.HK   //
//************************//



#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

const int xPin = 0;     //Connected to A0
const int yPin = 1;     //Connected to A1
const int zPin = 2;     //Connected to A2

int minVal = 300;
int maxVal = 400;
//to hold the caculated values

double ix;
double iy;
double iz;

//THis is BGR Color, NOT RGB, change the R and B in swap and worked
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI(SDA), pin 12 = MISO, pin 13 = SCL.
#define SD_CS    4  // Chip select line for SD card
#define TFT_CS  10  // Chip select line for TFT display
#define TFT_DC   9  // Data/command line for TFT
#define TFT_RST  8  // Reset line for TFT (or connect to +5V)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

int x, y;
int x_direction, y_direction;

void setup(void) {
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735R chip, black
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(GREEN);
  x = 0;
  y = 0;
  x_direction = 0;
  y_direction = 0;
  Serial.begin(9600);
}

void clear_text_line(int text_x, int text_y){
  for(int i = 0; i < 8; i++){
    tft.drawFastHLine(text_x, text_y + i, 100, BLACK);  
  }
}

void loop() {
  tft.setCursor(x,y);
  tft.println("WTF"); 
  delay(50);
  clear_text_line(x, y);
  Serial.print("X: ");
  Serial.println(x);
  Serial.print("X_DIR:");
  Serial.println(x_direction);
  
  if(x_direction == 0){
    if(128 - (3*7)+2 == x){
      x_direction = 1;
    }
    x++;
  } else{
    if(1 == x){
      x_direction = 0;
    }
    x--;
  }
  if(y_direction == 0){
    if(152 == y){
      y_direction = 1;
    }
    y++;
  } else{
    if(1 == y){
      y_direction = 0;
    }
    y--;
  }
}


void show_adxl() {

}



#define BUFFPIXEL 20

