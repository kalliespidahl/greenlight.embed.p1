#ifndef WEATHERDATA_H
#define WEATHERDATA_H

struct WindData {
   String time;
   float speed;
   float dir;
   String card;
   float gust;
};

struct WindParams {
    float minSpeed;
    float maxSpeed;
    float startDir;
    float endDir;
};

#endif
