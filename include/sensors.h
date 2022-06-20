#ifndef SENSORS_H_   /* Include guard */
#define SENSORS_H_
#include <BH1750.h>

typedef struct {
    int left, right, up, down;
    bool isLeft();
    bool isRight();
} LightSensor;

LightSensor lightReadings();

float readLightLevel();

void lightMeterSetup();

void setupLightMeter();

#endif