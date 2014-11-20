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

  Spark.function("led_strip", changeLedStrip);
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
int changeLedStrip(String command) {
    int redValue, blueValue, greenValue;
    uint16_t i, j;

    //strip.Color(redValue, greenValue, blueValue)
    if(command.substring(0.2) == "red") redValue = 255, blueValue = 0, greenValue = 0;
    else if(command.substring(0.4) == "green") redValue = 0, blueValue = 0, greenValue = 255;
    else if(command.substring(0.3) == "blue") redValue = 0, blueValue = 255, greenValue = 0;
    else return -1;

    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(redValue, greenValue, blueValue));
    }
    strip.show();
    return 1;
}
