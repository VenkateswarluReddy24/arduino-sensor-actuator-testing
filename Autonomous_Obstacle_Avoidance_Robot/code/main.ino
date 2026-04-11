/*
  🤖 Autonomous Obstacle Avoidance Robot (Ultrasonic + Servo Radar)

  Features:
  - Real-time obstacle detection
  - Servo-based environment scanning
  - Intelligent path decision (left/right)
  - Smooth motor control

  Author: Venkateswarlu Reddy
*/

#include <Servo.h>

// ---------------- PINS ----------------
#define SERVO_PIN 11
#define TRIG_PIN 3
#define ECHO_PIN 2

#define ENA 5
#define ENB 6

#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 12

// ---------------- PARAMETERS ----------------
#define SAFE_DISTANCE 35.0

#define FORWARD_SPEED 110
#define REVERSE_SPEED 135
#define TURN_SPEED 150

Servo radarServo;

// ---------------- MOTOR CONTROL ----------------
void moveMotor(int rightSpeed, int leftSpeed)
{
  digitalWrite(IN1, rightSpeed >= 0);
  digitalWrite(IN2, rightSpeed < 0);

  digitalWrite(IN3, leftSpeed >= 0);
  digitalWrite(IN4, leftSpeed < 0);

  analogWrite(ENA, abs(rightSpeed));
  analogWrite(ENB, abs(leftSpeed));
}

void stopBot()
{
  moveMotor(0, 0);
}

// ---------------- ULTRASONIC ----------------
float getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if(duration == 0) return 400;

  return duration * 0.0343 / 2.0;
}

// ---------------- FILTER ----------------
float getStableDistance()
{
  float total = 0;

  for(int i=0; i<4; i++)
  {
    total += getDistance();
    delay(25);
  }

  return total / 4.0;
}

// ---------------- SCANNING ----------------
float scan(int angle)
{
  radarServo.write(angle);
  delay(400);

  float distance = getStableDistance();

  Serial.print("[SCAN ");
  Serial.print(angle);
  Serial.print("] -> ");
  Serial.println(distance);

  return distance;
}

// ---------------- SETUP ----------------
void setup()
{
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  radarServo.attach(SERVO_PIN);
  radarServo.write(90);

  Serial.println("AUTONOMOUS ROBOT STARTED");
  delay(1000);
}

// ---------------- LOOP ----------------
void loop()
{
  float front = getStableDistance();

  Serial.print("Front: ");
  Serial.println(front);

  // -------- MOVE FORWARD --------
  if(front > SAFE_DISTANCE)
  {
    moveMotor(FORWARD_SPEED, FORWARD_SPEED);
    return;
  }

  // -------- OBSTACLE DETECTED --------
  stopBot();
  delay(150);

  float left  = scan(150);
  float right = scan(30);

  // -------- REVERSE FOR SPACE --------
  moveMotor(-REVERSE_SPEED, -REVERSE_SPEED);
  delay(250);

  stopBot();
  delay(100);

  // -------- DECISION --------
  if(left > right)
  {
    Serial.println("Decision: LEFT");
    moveMotor(-TURN_SPEED, TURN_SPEED);
  }
  else
  {
    Serial.println("Decision: RIGHT");
    moveMotor(TURN_SPEED, -TURN_SPEED);
  }

  delay(500);

  stopBot();

  radarServo.write(90);
}
