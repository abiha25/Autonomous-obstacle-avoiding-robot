#include <Servo.h>

Servo myServo;

void setup() {

  myServo.attach(7);

  myServo.write(90); // Center position
  delay(1000);
}

void loop() {

  // Move to 0°
  myServo.write(0);
  delay(1000);

  // Move to 90°
  myServo.write(90);
  delay(1000);

  // Move to 180°
  myServo.write(180);
  delay(1000);

  // Return to center
  myServo.write(90);
  delay(1000);
}