#ifndef LED_H
#define LED_H

#include <Arduino.h>

extern struct Color red;
extern struct Color green;
extern struct Color yellow;
extern struct Color purple;
extern struct Color blue;

struct Color {
    int8_t red;
    int8_t green;
    int8_t blue;
};

void setUpLed();

void setColor(struct Color color);

#endif
