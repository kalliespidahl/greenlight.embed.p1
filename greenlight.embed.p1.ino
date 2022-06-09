
#include <Ticker.h>

#include "src/greenlight.h"
#include "src/https.h"
#include "src/led.h"
#include "src/weatherData.h"
#include "src/wifi.h"

// TODO: Use Ticker to schedule the repeated greenlight checks

int ms = 1000;

// 10 minutes
int pollDelaySec = 60 * 10;

struct WindParams kalliesWindParams = {
    .minSpeed = 13.0, .startDir = 180, .endDir = 250};

// GREEN
// struct WindParams kalliesWindParams = {
//     .minSpeed = 0.0, .startDir = 0, .endDir = 360};

// YELLOW
// struct WindParams kalliesWindParams = {
//     .minSpeed = 99.0, .startDir = 0, .endDir = 360};

void setup() {
    Serial.begin(115200);
    delay(1);
    Serial.println();
    setUpWiFi();
    setUpLed();
    setUpGreenlight();
}

void loop() {
    greenlight(kalliesWindParams);

    delay(ms * pollDelaySec);
}
