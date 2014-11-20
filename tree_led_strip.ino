/*
 * This is a minimal example, see extra-examples.cpp for a version
 * with more explantory documentation, example routines, how to
 * hook up your pixels and all of the pixel types that are supported.
 *
 */

#include "application.h"
//#include "spark_disable_wlan.h" // For faster local debugging only
#include "neopixel/neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Spark.function("led_strip", receiveCommand);
}
void loop()
{
//   rainbow(100);
    delay(20);
}

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

//SparkCoreFunction
int receiveCommand(String command) {

    if(command.substring(0.2) == "red") solidLights(255, 0, 0);
    else if(command.substring(0.4) == "green") solidLights(0, 0, 255);
    else if(command.substring(0.3) == "blue") solidLights(0, 255, 0);
    else if(command.substring(0.6) == "mailjet") mailjetLight();
    else if(command.substring(0.8) == "christmas") christmasLight();
    else if(command.substring(0.6) == "rainbow") rainbow(100);
    else return -1;

    return 1;
}

int solidLights(int redValue, int blueValue, int greenValue) {
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
    int lightArray[2][3] = {{255, 0, 0}, {0, 0, 255}};
    int lightValueForArray = 0;
    for(i=0; i<strip.numPixels(); i++) {
      if(lightValueForArray > (sizeof(lightArray)/(3*sizeof(int)) - 1)) lightValueForArray = 0; //lightValueForArray > 1 where 1 is number of colors in array minus 1
      strip.setPixelColor(i, strip.Color(lightArray[lightValueForArray][0], lightArray[lightValueForArray][1], lightArray[lightValueForArray][2]));
      lightValueForArray += 1;
    }
    strip.show();
    return 1;
}
