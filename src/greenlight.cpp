
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

        boolean highWind = data.speed >= params.maxSpeed;
        boolean goodSpeed = data.speed >= params.minSpeed;
        boolean goodDir = data.dir >= params.startDir && data.dir <= params.endDir;
        //boolean wrongDir = data.dir <= params.startDir && data.dir >= params.endDir;

        if (highWind && goodDir) {
            // TWINTIP
            Serial.println("!! TWINTIP !!!");
            setColor(green);
        } else if (goodSpeed && goodDir) {
            // FOIL
            Serial.println("!! FOIL !!!");
            setColor(purple);
        } else if (goodSpeed) {
            // GOOD BUT WRONG DIRECTION
            Serial.println("!! GOOD BUT WRONG DIRECTION !!!");
            setColor(yellow);
        } else {
            // GET SHIT DONE
            Serial.println("!! GET SHIT DONE !!!");
            //setColor(red);
        }
    } else {
        Serial.print("Failure");
    }
}