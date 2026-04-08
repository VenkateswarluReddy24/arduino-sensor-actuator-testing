/*
  🐾 Automated Pet Feeder System (Timer-Based)

  Features:
  - Non-blocking timer using millis()
  - Smooth servo motion
  - Configurable feeding interval
  - Clean modular structure

  Author: Venkateswarlu Reddy
*/

#include <TM1637Display.h>
#include <Servo.h>

// ---------------- PINS ----------------
#define CLK 3
#define DIO 2
#define SERVO_PIN 9

// ---------------- CONFIG ----------------
#define FEED_INTERVAL 15     // seconds
#define SERVO_OPEN_ANGLE 0
#define SERVO_CLOSE_ANGLE 90
#define SERVO_STEP_DELAY 15

TM1637Display display(CLK, DIO);
Servo feederServo;

// ---------------- VARIABLES ----------------
unsigned long previousMillis = 0;
int seconds = FEED_INTERVAL;
bool feedingInProgress = false;
bool colonState = true;

// ---------------- FUNCTION DECLARATIONS ----------------
void updateDisplay();
void startFeeding();
void moveServoSmooth(int startAngle, int endAngle);

// ---------------- SETUP ----------------
void setup()
{
  display.setBrightness(7);
  feederServo.attach(SERVO_PIN);
  feederServo.write(SERVO_CLOSE_ANGLE);

  display.clear();
}

// ---------------- LOOP ----------------
void loop()
{
  unsigned long currentMillis = millis();

  // Timer update every second
  if (currentMillis - previousMillis >= 1000)
  {
    previousMillis = currentMillis;

    colonState = !colonState;

    updateDisplay();

    if (!feedingInProgress)
    {
      seconds--;

      if (seconds <= 0)
      {
        startFeeding();
        seconds = FEED_INTERVAL;
      }
    }
  }
}

// ---------------- DISPLAY ----------------
void updateDisplay()
{
  display.showNumberDecEx(
    seconds,
    colonState ? 0b01000000 : 0,
    true
  );
}

// ---------------- FEEDING LOGIC ----------------
void startFeeding()
{
  feedingInProgress = true;

  Serial.println("Feeding Started");

  // Open
  moveServoSmooth(SERVO_CLOSE_ANGLE, SERVO_OPEN_ANGLE);

  delay(2000); // dispense time

  // Close
  moveServoSmooth(SERVO_OPEN_ANGLE, SERVO_CLOSE_ANGLE);

  Serial.println("Feeding Completed");

  feedingInProgress = false;
}

// ---------------- SERVO CONTROL ----------------
void moveServoSmooth(int startAngle, int endAngle)
{
  if (startAngle < endAngle)
  {
    for (int pos = startAngle; pos <= endAngle; pos++)
    {
      feederServo.write(pos);
      delay(SERVO_STEP_DELAY);
    }
  }
  else
  {
    for (int pos = startAngle; pos >= endAngle; pos--)
    {
      feederServo.write(pos);
      delay(SERVO_STEP_DELAY);
    }
  }
}
