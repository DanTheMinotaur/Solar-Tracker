#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter(0x23);

struct LightSensor {
  int left, right, up, down;

  String toString() {
    return "Left: " + String(left) + "; Right: " + String(right) 
      + "; Up: " + String(up) + "; Down: " + String(down);
  }
};

LightSensor lightReadings() {
  LightSensor ls = (LightSensor) {\
    analogRead(A0), 
    analogRead(A1), 
    analogRead(A2), 
    analogRead(A3)
  };
  Serial.println(ls.toString());
  return ls;
}

float readLightLevel() {
  if (lightMeter.measurementReady()) {
    float lux = lightMeter.readLightLevel();
    Serial.print(F("Light: "));
    Serial.print(lux);
    Serial.println(F(" lx"));
    return lux;
  }
}

void setupLightMeter() {
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }
}