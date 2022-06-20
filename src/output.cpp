#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include "sensors.h"

LiquidCrystal_I2C lcd(0x27,16,2);
Servo x_servo, y_servo;

void lcdPrint(String val) {
    lcd.print(val);
}

void lcdSetup() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
}

void servoSetup() {
  x_servo.attach(9);
  y_servo.attach(10);
  x_servo.write(90);
  delay(200);
  y_servo.write(30);
  delay(200);
}

int percentage(int num1, int num2) {
  return 100 * min(num1, num2) / max(num1, num2);
}

void moveServo(Servo s, int destAngle, int minAngle = 10, int maxAngle = 170) {
  int currAngle = s.read();
  int increment = destAngle >= currAngle ? 5 : -5;
  while(currAngle != destAngle ) {
    currAngle += increment;
    s.write(currAngle);
    delay(100);
    if (currAngle <= minAngle || currAngle >= maxAngle) {
      break;
    }
  }
}

void moveX(int destAngle) {
  Serial.println("Moving X to " + String(destAngle));
  moveServo(x_servo, destAngle);
}

void moveY(int destAngle) {
  Serial.println("Moving Y to " + String(destAngle));
  moveServo(y_servo, destAngle, 1, 100);
}

void findLightIntensity() {
  float startLightLevel = readLightLevel();
  int servoStart = y_servo.read();
  moveY(servoStart + 5);
  delay(1000);
  float lightReading = readLightLevel();
  int move; // 0 = move down; 1 = move up

  if (lightReading <= startLightLevel) {
    moveY(servoStart - 5);
    delay(1000);
    lightReading = readLightLevel();
    if (lightReading <= startLightLevel) {
        moveY(servoStart);
        return;
    } else {
        move = 0;
    }
  } else {
    move = 1;
  }

  float lastLightReading;
  while(true) {
    int moveTo = (move) ? 5 : -5;
    moveY(y_servo.read() + moveTo);
    delay(800);
    if (lastLightReading == 0) {
      lastLightReading = readLightLevel();
    } else {
      if (lastLightReading <= readLightLevel()) {
        break;
      }
    }
  }
}

void findLightAngle() {
  LightSensor ls = lightReadings();
  int angle;
  if (ls.isLeft()) {
    angle = 90 + percentage(ls.down, ls.left);
  } else {
    angle = 90 - percentage(ls.down, ls.right);
  }
  // Round to nearest 5
  int result = angle + 5 / 2;
  result -= result % 5;
  moveX(result);
}

void moveToLight() {
  findLightAngle();
  findLightIntensity();  
}