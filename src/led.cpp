#include "led.h"
#include "leds/neopixel.h"
#include "leds/rgbled.h"

struct Color red = {.red = 255, .green = 0, .blue = 0};
struct Color green = {.red = 0, .green = 255, .blue = 0};
struct Color yellow = {.red = 255, .green = 255, .blue = 0};

#define USE_LED false

void setUpLed() {
    if (USE_LED) {
        setUpRgbLed();
    } else {
        setUpNeopixel();
    }
}

void setColor(struct Color color) {
    if (USE_LED) {
        setRgbLedColor(color);
    } else {
        setNeopixelColor(color);
    }
}
