#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
#include <BH1750.h>

LiquidCrystal_I2C lcd(0x27,16,2);

struct LightSensor {
  int left, right, up, down;

  String toString() {
    return "Left: " + String(left) + "; Right: " + String(right) 
      + "; Up: " + String(up) + "; Down: " + String(down);
  }

  boolean isLeft() {
    return left > right;
  }

  boolean isRight() {
    return right > left;
  }
};

Servo x_servo, y_servo;
const int movementDegrees = 10;
LightSensor lastReadings;

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

/*
Round values from light sensors

SERVO_MAX_LEFT = 10
SERVO_MAX_RIGHT = 170

Read light intesity
*/

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();

  uint8_t i_pins[] = {A0, A1, A2, A3};
  for (uint8_t a: i_pins) pinMode(a, INPUT);

  lcd.setCursor(0,0);

  lcd.print("Hello :-)");
  // lcd.setCursor(0,1);

  x_servo.attach(9);
  y_servo.attach(10);

  x_servo.write(90);
  delay(200);
  y_servo.write(30);

  moveX(40);

  Serial.begin(9600);
}

void testServo(Servo s) {
  s.write(10);
  Serial.println(10);
  delay(3000);
  s.write(90);
  Serial.println(90);
  delay(3000);
  s.write(170);
  Serial.println(170);
  delay(3000);
  s.write(90);
  Serial.println(90);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(lightReadings().toString());
  // delay(1000);

  // testServo(y_servo);
  delay(3000);
  moveToLight();

}