#include <ArduinoJson.h>

#include "noaa.h"
#include "https.h"

const char* host = "api.tidesandcurrents.noaa.gov";
const char* path = "/api/prod/datagetter";
const char* date = "latest";
const char* product = "wind";
const char* units = "english";
const char* time_zone = "lst_ldt";
const char* format = "json";

// Private function declarations

void urlBuilder(int station, char* url);
boolean parseJson(String windDataString, struct WindData* windData);

// Public function definitions

boolean getWindData(int station, struct WindData* data) {
    char pathAndParams[200] = {0};
    urlBuilder(station, pathAndParams);
    String response = connectToHttpsServer(host, pathAndParams);
    return parseJson(response, data);
}

// Private function definitions

void urlBuilder(int station, char* url) {
    snprintf(url, 200, "%s?date=%s&station=%d&product=%s&units=%s&time_zone=%s&format=%s",
             path, date, station, product, units, time_zone, format);
}

boolean parseJson(String windDataString, struct WindData* windData) {
  StaticJsonBuffer<512> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(windDataString);

    if (!root.success()) {
        Serial.println("parseObject() failed");
        return false;
    }

    String t = root["data"][0]["t"];
    String s = root["data"][0]["s"];
    String d = root["data"][0]["d"];
    String dr = root["data"][0]["dr"];
    String g = root["data"][0]["g"];

    windData->time = t;
    windData->speed = s.toFloat();
    windData->dir = d.toFloat();
    windData->card = dr;
    windData->gust = g.toFloat();

    return true;
}
