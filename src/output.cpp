#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include "sensors.h"

LiquidCrystal_I2C lcd(0x27,16,2);
Servo x_servo, y_servo;

/*
Round values from light sensors

SERVO_MAX_LEFT = 10
SERVO_MAX_RIGHT = 170

Read light intesity
*/

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

void moveX(int dest_angle) {
  Serial.println("Moving X to " + dest_angle);
  int curr_angle = x_servo.read();
  int increment = dest_angle >= curr_angle ? 5 : -5;
  while(curr_angle != dest_angle ) {
    curr_angle += increment;
    x_servo.write(curr_angle);
    delay(100);
    if (curr_angle <= 10 || curr_angle >= 170) {
      break;
    }
  }
  Serial.println("Movement Complete");
}

void moveToLight() {
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
  Serial.println("Movement Complete");
}