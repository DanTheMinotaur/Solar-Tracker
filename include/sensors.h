#ifndef SENSORS_H_   /* Include guard */
#define SENSORS_H_
#include <BH1750.h>

typedef struct LightSensor {
  int left, right, up, down;
  boolean isLeft() {
    return left > right;
  }

  boolean isRight() {
    return right > left;
  }
} LightSensor;

LightSensor lightReadings();

float readLightLevel();

void lightMeterSetup();

void setupLightMeter();

#endif