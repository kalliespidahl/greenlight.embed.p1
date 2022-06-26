
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


// struct WindParams TTWindParams = {
//     .minSpeed = 17.0, .startDir = 180, .endDir = 270};

// struct WindParams FoilWindParams = {
//     .minSpeed = 11.0, .startDir = 180, .endDir = 270};

// struct WindParams packWindParams = {
//     .minSpeed = 9.0, .startDir = 180, .endDir = 270};


// kalliesWindParams
struct WindParams kalliesWindParams = {
    .minSpeed = 11.0, .maxSpeed = 16.99, .startDir = 160, .endDir = 270};


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
