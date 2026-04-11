/*
  📡 Ultrasonic Radar System (Servo Scanning + Object Detection)

  Features:
  - 180° radar scanning using servo motor
  - Ultrasonic distance measurement (HC-SR04)
  - Noise reduction using averaging filter
  - Buzzer alert with hysteresis control
  - Serial output for visualization (Radar plotting)

  Author: Venkateswarlu Reddy
*/

#include <Servo.h>

// ---------------- PINS ----------------
#define TRIG_PIN   10
#define ECHO_PIN   11
#define SERVO_PIN  12
#define BUZZER_PIN 8

// ---------------- PARAMETERS ----------------
#define MIN_DISTANCE 2
#define MAX_DISTANCE 200
#define ALERT_ON_DISTANCE 30
#define ALERT_OFF_DISTANCE 35

#define SAMPLE_COUNT 3
#define SERVO_DELAY 25

Servo radarServo;

// ---------------- VARIABLES ----------------
bool buzzerState = false;

// ================= DISTANCE FUNCTION =================
int getDistance()
{
  long total = 0;

  for (int i = 0; i < SAMPLE_COUNT; i++)
  {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(3);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);

    if (duration == 0) return MAX_DISTANCE;

    int distance = duration * 0.0343 / 2;

    distance = constrain(distance, MIN_DISTANCE, MAX_DISTANCE);

    total += distance;
    delay(5);
  }

  return total / SAMPLE_COUNT;
}

// ================= RADAR SWEEP =================
void radarSweep(int startAngle, int endAngle, int step)
{
  for (int angle = startAngle; angle != endAngle; angle += step)
  {
    radarServo.write(angle);
    delay(SERVO_DELAY);

    int distance = getDistance();

    handleBuzzer(distance);

    // Serial format for radar visualization tools
    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.println(".");
  }
}

// ================= BUZZER CONTROL =================
void handleBuzzer(int distance)
{
  if (distance < ALERT_ON_DISTANCE && !buzzerState)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    buzzerState = true;
  }

  else if (distance > ALERT_OFF_DISTANCE && buzzerState)
  {
    digitalWrite(BUZZER_PIN, LOW);
    buzzerState = false;
  }
}

// ================= SETUP =================
void setup()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);

  Serial.begin(9600);

  radarServo.attach(SERVO_PIN);
  radarServo.write(90);

  delay(1000);
}

// ================= LOOP =================
void loop()
{
  radarSweep(15, 165, 1);
  radarSweep(165, 15, -1);
}
