/*
  🚀 Servo Motor Control Module (Precision + Smooth Motion)

  Features:
  - Smooth angle transition
  - Configurable limits
  - Reusable function design
  - Safe movement control

  Author: Venkateswarlu Reddy
*/

#include <Servo.h>

#define SERVO_PIN 9

#define MIN_ANGLE 0
#define MAX_ANGLE 180
#define STEP_DELAY 10   // Speed of movement (lower = faster)

Servo myServo;

int currentAngle = 90; // Start from center

void setup() {
  Serial.begin(9600);
  
  myServo.attach(SERVO_PIN);
  myServo.write(currentAngle);

  Serial.println(F("\n=============================="));
  Serial.println(F(" SERVO MOTOR TEST MODULE "));
  Serial.println(F("=============================="));
  Serial.println(F("Smooth motion enabled\n"));
}

void loop() {
  // Sweep from MIN to MAX
  moveServoSmooth(currentAngle, MAX_ANGLE);

  delay(500);

  // Sweep back from MAX to MIN
  moveServoSmooth(MAX_ANGLE, MIN_ANGLE);

  delay(500);
}

// 🔄 Smooth movement function
void moveServoSmooth(int startAngle, int endAngle) {

  if (startAngle < endAngle) {
    for (int angle = startAngle; angle <= endAngle; angle++) {
      myServo.write(angle);
      currentAngle = angle;
      delay(STEP_DELAY);
    }
  } 
  else {
    for (int angle = startAngle; angle >= endAngle; angle--) {
      myServo.write(angle);
      currentAngle = angle;
      delay(STEP_DELAY);
    }
  }
}
