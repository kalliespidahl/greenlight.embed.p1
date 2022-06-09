#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

#include "../led.h"

void setUpRgbLed();
void setRgbLedColor(struct Color color);

#endif