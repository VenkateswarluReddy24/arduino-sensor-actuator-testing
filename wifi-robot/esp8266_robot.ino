/*
  🚀 WiFi Controlled Robot (Stable + Professional Version)

  Features:
  - Clean motor abstraction
  - Safe speed handling
  - Maintain original behavior (no auto stop issue)
  - Scalable architecture

  Author: Venkateswarlu Reddy
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ---------------- WIFI ----------------
const char* ssid = "YOUR WIFI NAME";
const char* password = "YOUR WIFI PASSWORD";

ESP8266WebServer server(80);

// ---------------- MOTOR PINS ----------------
#define IN1 D1
#define IN2 D2
#define IN3 D5
#define IN4 D6
#define ENA D7
#define ENB D8

#define MAX_PWM 1023

int speedValue = 1023;

// ---------------- FUNCTION DECLARATIONS ----------------
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopRobot();
void setSpeed();
void setMotor(int in1, int in2, bool direction);

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWriteRange(MAX_PWM);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  WiFi.softAP(ssid, password);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);

  Serial.print("Robot IP: ");
  Serial.println(WiFi.softAPIP());

  // API routes
  server.on("/forward", moveForward);
  server.on("/back", moveBackward);
  server.on("/left", turnLeft);
  server.on("/right", turnRight);
  server.on("/stop", stopRobot);
  server.on("/speed", setSpeed);

  server.begin();

  Serial.println("🚀 Robot Server Ready");
}

// ---------------- LOOP ----------------
void loop() {
  server.handleClient();
}

// ---------------- MOTOR CONTROL ----------------

// Generic motor control (reusable)
void setMotor(int in1, int in2, bool forward) {
  digitalWrite(in1, forward);
  digitalWrite(in2, !forward);
}

// ---------------- MOVEMENT ----------------

void moveForward() {
  Serial.println("Forward");

  setMotor(IN1, IN2, true);
  setMotor(IN3, IN4, true);

  server.send(200, "text/plain", "OK");
}

void moveBackward() {
  Serial.println("Backward");

  setMotor(IN1, IN2, false);
  setMotor(IN3, IN4, false);

  server.send(200, "text/plain", "OK");
}

void turnLeft() {
  Serial.println("Left");

  setMotor(IN1, IN2, false);
  setMotor(IN3, IN4, true);

  server.send(200, "text/plain", "OK");
}

void turnRight() {
  Serial.println("Right");

  setMotor(IN1, IN2, true);
  setMotor(IN3, IN4, false);

  server.send(200, "text/plain", "OK");
}

void stopRobot() {
  Serial.println("Stop");

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  server.send(200, "text/plain", "OK");
}

// ---------------- SPEED CONTROL ----------------

void setSpeed() {

  int sliderValue = server.arg("value").toInt();

  // Safety constrain
  sliderValue = constrain(sliderValue, 0, 255);

  speedValue = map(sliderValue, 0, 255, 0, MAX_PWM);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  Serial.print("Speed PWM: ");
  Serial.println(speedValue);

  server.send(200, "text/plain", "OK");
}
