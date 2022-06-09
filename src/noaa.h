#ifndef NOAA_H
#define NOAA_H

#include <Arduino.h>

#include "weatherData.h"

boolean getWindData(int station, struct WindData* data);

#endif