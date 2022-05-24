#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,16,2);

struct LightSensor {
  int left, right, up, down;

  String toString() {
    return "Left: " + String(left) + "; Right: " + String(right) 
      + "; Up: " + String(up) + "; Down: " + String(down);
  }
};

Servo x_servo, y_servo;

LightSensor lightReadings() {
  return (LightSensor) {\
    analogRead(A0), 
    analogRead(A1), 
    analogRead(A2), 
    analogRead(A3)
  };
}

/*
Round values from light sensors

Loop
  Check L / R sensor
  

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

  // x_servo.attach(9);
  y_servo.attach(10);

  // x_servo.write(90);
  y_servo.write(10);

  // delay(3000);
  // y_servo.write(50);

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
}