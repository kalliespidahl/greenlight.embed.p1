#include <Adafruit_NeoPixel.h>

#include "neopixel.h"

// https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use

#define PIN D4

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

void setUpNeopixel() {
    strip.begin();
    strip.show();
    setNeopixelColor({0, 0, 0});
}

void setNeopixelColor(struct Color color) {
    strip.setPixelColor(0, color.red, color.green, color.blue);
    strip.show();
    strip.setBrightness(50);
}
