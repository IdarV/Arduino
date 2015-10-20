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
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
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

void setup(void) {
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735R chip, red tab
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(WHITE);
  tft.println( "Accel: " ); 
  tft.setCursor(0,110);
  tft.println("  1.8 TFT + ADXL335  ");
  tft.setCursor(0,120);
  tft.println("Arduino Balance Scale");
  tft.setTextColor(CYAN);
  tft.setCursor(0,130);
  tft.println("****** Example ******");
  tft.setTextSize(2);
  tft.setTextColor(MAGENTA);
  tft.setCursor(0,140);
  tft.println("- WIDE.HK-"); 
}

void loop() {
  // int k=0;

  //tft.setCursor(0,0);
  // tft.println(millis()/10);
  show_adxl() ;

  //tft.clearDisplay();
}


void show_adxl() {
  while(1)
  {
    int xRead = analogRead(xPin);
    int yRead = analogRead(yPin);
    int zRead = analogRead(zPin);

    int xAng = map(xRead, minVal, maxVal, -90, 90);
    int yAng = map(yRead, minVal, maxVal, -90, 90);
    int zAng = map(zRead, minVal, maxVal, -90, 90);

    ix = (RAD_TO_DEG * (atan2(-yAng, -zAng) + PI));
    iy = (RAD_TO_DEG * (atan2(-xAng, -zAng) + PI));
    iz = (RAD_TO_DEG * (atan2(-yAng, -xAng) + PI));

    tft.setCursor(0,0);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(40,0);
    tft.println("X");
    tft.setCursor(40,10); 
    tft.println((float) ix, 0 );   //x

    tft.setCursor(70,0);
    tft.println("Y");
    tft.setCursor(70,10); 
    tft.println((float) iy, 0 );   //y

    tft.setCursor(100,0);
    tft.println("Z");
    tft.setCursor(100,10);
    tft.println((float) iz, 0 );   //z





    tft.drawCircle(65, 60, 30, GREEN);
    tft.fillCircle(iy+65, ix+60, 4, BLUE);

    tft.drawFastVLine(iy+65, 32, 55, YELLOW);
    tft.drawFastHLine(38, ix+60, 55, RED);
    delay(20);
    tft.drawFastHLine(38, ix+60, 55, BLACK);
    tft.drawFastVLine(iy+65, 32, 55, BLACK);
    tft.fillCircle(iy+65, ix+60, 4, BLACK);
    tft.setTextColor(BLACK);
    tft.setCursor(40,10); 
    tft.println((float) ix, 0 );   //x
    tft.setCursor(70,10); 
    tft.println((float) iy, 0 );   //y
    tft.setCursor(100,10);
    tft.println((float) iz, 0 );   //z


  }
}



#define BUFFPIXEL 20

