
// LED Lights
#include "application.h"
//#include "spark_disable_wlan.h" // For faster local debugging only
#include "neopixel/neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN A5
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
// /LED Lights

//RGB Matrix
// This #include statement was automatically added by the Spark IDE.
#include "SparkIntervalTimer/SparkIntervalTimer.h"

// This #include statement was automatically added by the Spark IDE.
// #include "neopixel__spark_internet_button/neopixel__spark_internet_button.h"

// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_mfGFX/Adafruit_mfGFX.h"

// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.


#if defined(SPARK)
#include "Adafruit_mfGFX/Adafruit_mfGFX.h"   // Core graphics library
#include "RGBmatrixPanel/RGBmatrixPanel.h" // Hardware-specific library
#include "math.h"
#else
#include <avr/pgmspace.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#endif

#if defined(SPARK)
#define CLK D6
#define OE  D7
#define LAT A4
#define A   A0
#define B   A1
#define C   A2
#else
#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
#endif

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
// /RGB Matrix



void setup() {

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Spark.function("led_strip", receiveCommandLedStrip);
  Spark.function("dot_matrix", receiveCommandDotMatrix);
  Spark.function("background", receiveCommandBackground);

  matrix.begin();
}

void loop() {

  delay(20);
}

//LED Strip
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else if(WheelPos < 170) {
      WheelPos -= 85;
      return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
      } else {
        WheelPos -= 170;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
      }
    }

    //

//SparkCoreFunction for LED Strip
int receiveCommandLedStrip(String command) {

  if(command.substring(0.2) == "red") solidLights(255, 0, 0);
  else if(command.substring(0.4) == "green") solidLights(0, 255, 0);
  else if(command.substring(0.3) == "blue") solidLights(0, 0, 255);
  else if(command.substring(0.6) == "mailjet") mailjetLight();
  else if(command.substring(0.8) == "christmas") christmasLight();
  else if(command.substring(0.6) == "rainbow") rainbow(100);
  else return -1;

  return 1;
}

int solidLights(int redValue, int greenValue, int blueValue) {
  //strip.Color(redValue, greenValue, blueValue)
  uint16_t i, j;
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(redValue, greenValue, blueValue));
  }
  strip.show();
  return 1;
}

int mailjetLight() {
  // int mailjetOrange[] = {255, 191, 64};
  // int mailjetBlueGrey[] = {238, 237, 243};
  // int mailjetLightBlack[] = {41, 44, 51};
  // int mailjetLightGrey[] = {230, 230, 230};
  // int mailjetWhite[] = {52, 152, 219};
  uint16_t i, j;
  int lightArray[2][3] = {{255, 204, 0}, {238, 237, 243}};
  int lightValueForArray = 0;
  for(i=0; i<strip.numPixels(); i++) {
    if(lightValueForArray > (sizeof(lightArray)/(3*sizeof(int)) - 1)) lightValueForArray = 0; //lightValueForArray > 1 where 1 is number of colors in array minus 1
    strip.setPixelColor(i, strip.Color(lightArray[lightValueForArray][0], lightArray[lightValueForArray][1], lightArray[lightValueForArray][2]));
    lightValueForArray += 1;
  }
  strip.show();
  return 1;
}

int christmasLight() {
  // int mailjetOrange[] = {255, 191, 64};
  // int mailjetBlueGrey[] = {238, 237, 243};
  // int mailjetLightBlack[] = {41, 44, 51};
  // int mailjetLightGrey[] = {230, 230, 230};
  // int mailjetWhite[] = {52, 152, 219};
  uint16_t i, j;
  int lightArray[2][3] = {{255, 0, 0}, {0, 255, 0}};
  int lightValueForArray = 0;
  for(i=0; i<strip.numPixels(); i++) {
    if(lightValueForArray > (sizeof(lightArray)/(3*sizeof(int)) - 1)) lightValueForArray = 0; //lightValueForArray > 1 where 1 is number of colors in array minus 1
    strip.setPixelColor(i, strip.Color(lightArray[lightValueForArray][0], lightArray[lightValueForArray][1], lightArray[lightValueForArray][2]));
    lightValueForArray += 1;
  }
  strip.show();
  return 1;
}

//Sparkcore function for LED dot matrix shape
int receiveCommandDotMatrix(String command) {
  if(command.substring(0.3) == "star") star();
  else if(command.substring(0.5) == "circle") circle();
  else if(command.substring(0.6) == "mailjet") mailjetMatrix();
  else if(command.substring(0.3) == "logo") mailjetLogo();
  else return -1;

  return 1;
}

int star() {
  matrix.drawLine(14, 0, 13, 5, matrix.Color333(7, 0, 0)); // 1
  matrix.drawLine(13, 5, 6, 5, matrix.Color333(7, 0, 0)); //2
  matrix.drawLine(6, 5, 11, 10, matrix.Color333(7, 0, 0)); //3
  matrix.drawLine(11, 10, 9, 15, matrix.Color333(7, 0, 0)); //4
  matrix.drawLine(9, 15, 14, 11, matrix.Color333(7, 0, 0)); //5
  matrix.drawLine(14, 11, 20, 15, matrix.Color333(7, 0, 0));//6
  matrix.drawLine(20, 15, 18, 10, matrix.Color333(7, 0, 0));//7
  matrix.drawLine(18, 10, 23, 5, matrix.Color333(7, 0, 0));//8
  matrix.drawLine(23, 5, 16, 5, matrix.Color333(7, 0, 0));//9
  matrix.drawLine(16, 5, 14, 0, matrix.Color333(7, 0, 0));//10
  delay(500);
  return 1;
}

int circle() {
  // draw a blue circle (x center, y center, radius)
  matrix.fillCircle(15, 7, 7, matrix.Color333(7, 0, 7));
  delay(500);
  return 1;
}

int mailjetMatrix() {
  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(238, 237, 243));
  matrix.print('m');
  matrix.setTextColor(matrix.Color333(238, 237, 243));
  matrix.print('a');
  matrix.setTextColor(matrix.Color333(238, 237, 243));
  matrix.print('i');
  matrix.setTextColor(matrix.Color333(238, 237, 243));
  matrix.print('l');

  matrix.setCursor(14, 9);   // next line
  matrix.setTextColor(matrix.Color333(255, 204, 0));
  matrix.print('j');
  matrix.setTextColor(matrix.Color333(255, 204, 0));
  matrix.print('e');
  matrix.setTextColor(matrix.Color333(255, 204, 0));
  matrix.print('t');

  return 1;

}

int mailjetLogo() {
  //Create logo
  matrix.drawLine(1, 1, 29, 4, matrix.Color333(238, 237, 243)); // 1
  matrix.drawLine(29, 4, 9, 6, matrix.Color333(238, 237, 243)); //2
  matrix.drawLine(9, 6, 1, 1, matrix.Color333(238, 237, 243)); //3
  matrix.drawLine(9, 7, 28, 6, matrix.Color333(255, 204, 0)); //4
  matrix.drawLine(28, 6, 1, 14, matrix.Color333(255, 204, 0)); //5
  matrix.drawLine(1, 14, 9, 7, matrix.Color333(255, 204, 0));//6

  return 1;

}


//Sparkcore function for LED dot matrix background
int receiveCommandBackground(String command) {
  matrix.fillScreen(matrix.Color333(0, 0, 0)); //erase everything (Only do here and not in shape function because this POST request is done first on the server)
  if(command.substring(0.2) == "red") solidBackground(255, 0, 0);
  else if(command.substring(0.4) == "green") solidBackground(0, 255, 0);
  else if(command.substring(0.3) == "blue") solidBackground(0, 0, 255);
  else if(command.substring(0.4) == "blank" || command.substring(0.4) == "black" || command.substring(0.6) == "nothing") solidBackground(0, 0, 0);
  else return -1;

  return 1;
}

int solidBackground(int redValue, int greenValue, int blueValue) {
  matrix.fillScreen(matrix.Color333(redValue, greenValue, blueValue)); //clear board
  return 1;
}
