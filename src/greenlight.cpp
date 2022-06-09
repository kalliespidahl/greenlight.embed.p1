
#include "greenlight.h"
#include "led.h"
#include "noaa.h"

int hollandWindStation = 9087031;

void setUpGreenlight() {
    // Init LEDs or something
}

void greenlight(WindParams params) {
    Serial.println("Greenlight");

    struct WindData data;

    if (getWindData(hollandWindStation, &data)) {
        Serial.print("time: ");
        Serial.println(data.time);
        Serial.print("speed: ");
        Serial.println(data.speed);
        Serial.print("dir: ");
        Serial.println(data.dir);
        Serial.print("card: ");
        Serial.println(data.card);
        Serial.print("gust: ");
        Serial.println(data.gust);

        boolean goodSpeed = data.speed >= params.minSpeed;
        boolean goodDir = data.dir >= params.startDir && data.dir <= params.endDir;

        if (goodSpeed && goodDir) {
            // GREEN
            Serial.println("!! GREEN !!!");
            setColor(green);
        } else if (goodSpeed || goodDir) {
            // YELLOW
            Serial.println("!! YELLOW !!!");
            setColor(yellow);
        } else {
            // RED
            Serial.println("!! RED !!!");
            setColor(red);
        }
    } else {
        Serial.print("Failure");
    }
}
