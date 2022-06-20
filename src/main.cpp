#include <Arduino.h>
#include "sensors.h"
#include "output.h"

const int movementDegrees = 10;
LightSensor lastReadings;

void setup() {
  uint8_t i_pins[] = {A0, A1, A2, A3};
  for (uint8_t a: i_pins) pinMode(a, INPUT);

  lcdSetup();

  lcdPrint("Hello :-)");

  servoSetup();

  Serial.begin(9600);

  setupLightMeter();
}

void loop() {
  delay(5000);
  // moveToLight();
  // lightReadings();
  // readLightLevel();
  // delay(3000);
  // moveY(5);
  // readLightLevel();
  // delay(3000);
  // moveY(60);
  // readLightLevel();
  moveToLight();
}