
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library

// ST7789 TFT module connections
#define TFT_CS    10  // define chip select pin
#define TFT_DC     9  // define data/command pin
#define TFT_RST    8  // define reset pin, or set to -1 and connect to Arduino RESET pin

// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


#define MAX_WIDTH 320
#define MAX_LENGTH 240

int pot = 0;

int i = 0;

int x0 = 0;
int y0 = 0;
int x1 = 0;
int y1 = 0;
int colour = 0;

int x0Prev = x0;
int y0Prev = y0;
int x1Prev = x1;
int y1Prev = y1;


void setup() {

  // if the display has CS pin try with SPI_MODE0
  tft.init(MAX_LENGTH, MAX_WIDTH);    // Init ST7789 display 240x240 pixel

  // if the screen is flipped, remove this command
  tft.setRotation(3);

  tft.fillScreen(ST77XX_BLACK);

  Serial.begin(9600);


}

void loop() {


  pot = map(analogRead(A0), 0, 1023, 0, 100);


    if (x0 != x0Prev || y0 != y0Prev || x1 != x1Prev || y1 != y1Prev) {
      tft.drawLine(x0Prev, y0Prev, x1Prev, y1Prev, 0);
      tft.drawCircle(x0Prev, y0Prev,  y1Prev, 0);
      //  tft.fillScreen(ST77XX_BLACK);
      x0Prev = x0;
      y0Prev = y0;
      x1Prev = x1;
      y1Prev = y1;
    }


  //SYNTHWAVE 3D GRAPH

  //          for (int i = 0; i < 319; i++) {
  //
  //            x0 = tan(i) * 80 + 110;
  //            y0 = cos(i) * 80 + 110;
  //            x1 = sin(i) * 80 + 110;
  //            y1 = sin(i) * pot + 110;
  //            colour = randX * 150;
  //
  //            tft.drawLine(x0, y0, x1, y1, colour);
  //          }


//SIMPLE CIRCLE

  x0 = 160;
  y0 = 120;
  y1 = pot;
  colour = 65000;


  tft.drawCircle(x0, y0, y1, colour);


}
