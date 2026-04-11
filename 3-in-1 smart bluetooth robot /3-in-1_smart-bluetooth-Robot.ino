/*
  🤖 Bluetooth Controlled Smart Robot (3-in-1 System)

  Features:
  - Bluetooth control (HC-05)
  - Smooth speed ramping
  - Multi-speed control
  - Fail-safe stop mechanism
  - Modular motor control

  Author: Venkateswarlu Reddy
*/

#include <SoftwareSerial.h>

// ---------------- BLUETOOTH ----------------
SoftwareSerial BT(2, 3); // RX, TX

// ---------------- MOTOR DRIVER ----------------
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10

#define ENA 5
#define ENB 6

// ---------------- CONTROL VARIABLES ----------------
char cmd = 'S';

int currentSpeed = 0;
int targetSpeed = 160;

#define SPEED_STEP 5
#define LOOP_DELAY 20

// ---------------- SETUP ----------------
void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
  BT.begin(9600);

  Serial.println("SMART BLUETOOTH ROBOT READY");
}

// ---------------- LOOP ----------------
void loop() {

  readBluetooth();
  updateSpeed();
  executeCommand();

  delay(LOOP_DELAY);
}

// ---------------- READ COMMAND ----------------
void readBluetooth() {

  if (BT.available()) {
    cmd = BT.read();

    Serial.print("CMD: ");
    Serial.println(cmd);

    handleSpeedCommand(cmd);
  }
}

// ---------------- SPEED HANDLER ----------------
void handleSpeedCommand(char c) {

  switch (c) {
    case '1': targetSpeed = 100; break;
    case '2': targetSpeed = 150; break;
    case '3': targetSpeed = 200; break;
    case '4': targetSpeed = 255; break;
  }
}

// ---------------- SPEED RAMPING ----------------
void updateSpeed() {

  if (currentSpeed < targetSpeed)
    currentSpeed += SPEED_STEP;
  else if (currentSpeed > targetSpeed)
    currentSpeed -= SPEED_STEP;

  currentSpeed = constrain(currentSpeed, 0, 255);
}

// ---------------- COMMAND EXECUTION ----------------
void executeCommand() {

  switch (cmd) {

    case 'U': moveForward(); break;
    case 'D': moveBackward(); break;
    case 'L': turnLeft(); break;
    case 'R': turnRight(); break;
    case 'S': stopRobot(); break;

    default:  stopRobot(); break;
  }
}

// ---------------- MOTOR CONTROL ----------------
void setMotor(int leftSpeed, int rightSpeed,
              int l1, int l2, int r1, int r2) {

  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);

  digitalWrite(IN1, l1);
  digitalWrite(IN2, l2);
  digitalWrite(IN3, r1);
  digitalWrite(IN4, r2);
}

// ---------------- MOVEMENTS ----------------
void moveForward() {
  setMotor(currentSpeed, currentSpeed, HIGH, LOW, HIGH, LOW);
}

void moveBackward() {
  setMotor(currentSpeed, currentSpeed, LOW, HIGH, LOW, HIGH);
}

void turnLeft() {
  setMotor(currentSpeed, currentSpeed, LOW, HIGH, HIGH, LOW);
}

void turnRight() {
  setMotor(currentSpeed, currentSpeed, HIGH, LOW, LOW, HIGH);
}

void stopRobot() {
  setMotor(0, 0, LOW, LOW, LOW, LOW);
}
