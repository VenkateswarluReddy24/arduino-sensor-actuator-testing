/*
  🌧️ Automatic Rain Detection & Protection System

  Features:
  - Rain detection using analog sensor
  - Noise filtering with averaging
  - State-based confirmation system
  - Smooth servo-controlled cover mechanism

  Author: Venkateswarlu Reddy
*/

#include <Servo.h>

// ---------------- PINS ----------------
#define RAIN_ANALOG   A0
#define RAIN_DIGITAL  7
#define SERVO_PIN     9

// ---------------- PARAMETERS ----------------
#define RAIN_THRESHOLD 400
#define DRY_THRESHOLD  500

#define SAMPLE_COUNT   10
#define CONFIRM_COUNT  3

#define LOOP_DELAY     400

// ---------------- SERVO POSITIONS ----------------
#define OPEN_POS   90   // No rain
#define CLOSE_POS  0    // Rain detected

// ---------------- VARIABLES ----------------
Servo rainServo;

int rainState = 0;
int lastRainState = -1;

int rainConfirm = 0;
int dryConfirm = 0;

// ---------------- FILTER FUNCTION ----------------
int getFilteredValue()
{
  long total = 0;

  for(int i=0; i<SAMPLE_COUNT; i++)
  {
    total += analogRead(RAIN_ANALOG);
    delay(3);
  }

  return total / SAMPLE_COUNT;
}

// ---------------- SERVO CONTROL ----------------
void moveServoSmooth(int startPos, int endPos)
{
  int step = (startPos < endPos) ? 2 : -2;

  for(int pos = startPos; pos != endPos; pos += step)
  {
    rainServo.write(pos);
    delay(15);
  }

  rainServo.write(endPos);
}

// ---------------- SETUP ----------------
void setup()
{
  Serial.begin(9600);

  pinMode(RAIN_ANALOG, INPUT);
  pinMode(RAIN_DIGITAL, INPUT);

  rainServo.attach(SERVO_PIN);
  rainServo.write(OPEN_POS);

  Serial.println("RAIN SYSTEM INITIALIZED");
}

// ---------------- LOOP ----------------
void loop()
{
  int sensorValue = getFilteredValue();

  Serial.print("Sensor: ");
  Serial.println(sensorValue);

  // -------- STATE DETECTION --------
  if(sensorValue < RAIN_THRESHOLD)
  {
    rainConfirm++;
    dryConfirm = 0;
  }
  else if(sensorValue > DRY_THRESHOLD)
  {
    dryConfirm++;
    rainConfirm = 0;
  }

  // -------- CONFIRMATION --------
  if(rainConfirm >= CONFIRM_COUNT)
  {
    rainState = 1;
    rainConfirm = 0;
  }

  if(dryConfirm >= CONFIRM_COUNT)
  {
    rainState = 0;
    dryConfirm = 0;
  }

  // -------- ACTION --------
  if(rainState != lastRainState)
  {
    if(rainState == 1)
    {
      Serial.println("🌧️ Rain Detected → Closing");
      moveServoSmooth(OPEN_POS, CLOSE_POS);
    }
    else
    {
      Serial.println("☀️ No Rain → Opening");
      moveServoSmooth(CLOSE_POS, OPEN_POS);
    }

    lastRainState = rainState;
  }

  delay(LOOP_DELAY);
}
