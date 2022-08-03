
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
#define BUFFER_LENGTH 20
#define UPDATE_INTERVAL 300 //ms

int pot = 0;

int x0[BUFFER_LENGTH];
int y0[BUFFER_LENGTH];
int x1[BUFFER_LENGTH];
int y1[BUFFER_LENGTH];
int colour = 0;
int buffer_position = 0;

unsigned long last_update;

int alpha = 0;
int alpha_max=320;

void setup() {

  // if the display has CS pin try with SPI_MODE0
  tft.init(MAX_LENGTH, MAX_WIDTH);    // Init ST7789 display 240x240 pixel

  // if the screen is flipped, remove this command
  tft.setRotation(3);

  tft.fillScreen(ST77XX_BLACK);

  Serial.begin(9600);

  last_update=millis();
  
  for (int i = 0; i < BUFFER_LENGTH; i++) {
    x0[i]=0;
    y0[i]=0;
    x1[i]=0;
    y1[i]=0;
  }
}

void loop() {

  if (millis()-last_update>=UPDATE_INTERVAL) {
    
    // pick color and read pot
    int randC = random(0, 65000);
    pot = map(analogRead(A0), 0, 1023, 0, 100);
    
    // determine new line
    x0[buffer_position] = tan(alpha) * 80 + 110;
    y0[buffer_position] = cos(alpha) * 80 + 110;
    x1[buffer_position] = sin(alpha) * 80 + 110;
    y1[buffer_position] = sin(alpha) * pot + 110;
    colour = randC;
    alpha++;
    alpha%=alpha_max;

    // draw new line
    tft.drawLine(x0[buffer_position], y0[buffer_position], x1[buffer_position], y1[buffer_position], colour);
    
    // increase buffer position
    buffer_position++;
    buffer_position%=BUFFER_LENGTH;
    
    // clear the oldest line
    tft.drawLine(x0[buffer_position], y0[buffer_position], x1[buffer_position], y1[buffer_position], 0);
    
    // reset timer
    last_update = millis();
  }


//MY DODGY ATTEMPT AT THE SAME THING WITHOUT A FOR
//  if (i < 320) {
//    i++;
//    x0 = tan(i) * 80 + 110;
//    y0 = cos(i) * 80 + 110;
//    x1 = sin(i) * 80 + 110;
//    y1 = sin(i) * pot + 110;
//    colour = randX * 150;
//
//    tft.drawLine(x0, y0, x1, y1, colour);
//  }
//
//
//  else {
//    i = 0;
//  }


  //SIMPLE CIRCLE

  //  x0 = 160;
  //  y0 = 120;
  //  y1 = pot;
  //  colour = 65000;
  //
  //
  //  tft.drawCircle(x0, y0, y1, colour);


}
