/*
  ============================================================
       🚀 WiFi Robot
       ESP8266 LoLin + L298N
       ESP Wi-fi Car Controller App
  ============================================================

  WebSocket Commands:

  F  = Forward
  B  = Backward
  L  = Left
  R  = Right
  S  = Stop

  E  = Forward Right
  Q  = Forward Left
  C  = Backward Right
  Z  = Backward Left

  V0-V9 = Speed levels
  VA    = Maximum speed

  H/h = F1 ON/OFF
  K/k = F2 ON/OFF
  T/t = F3 ON/OFF

  Safety:
  - 3 second command watchdog
  - Safe startup
  - Automatic stop on communication timeout
  - Non-blocking loop

  Author: Venkateswarlu Reddy
*/

#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

// ============================================================
// WIFI
// ============================================================

const char* ssid = "Wifi Robot";
const char* password = "12345678";

// ============================================================
// WEBSOCKET SERVER
// ============================================================

WebSocketsServer webSocket = WebSocketsServer(80);

// ============================================================
// MOTOR PINS
// ============================================================

#define IN1 D1
#define IN2 D2

#define IN3 D5
#define IN4 D6

#define ENA D7
#define ENB D8

// ============================================================
// PWM
// ============================================================

#define MAX_PWM 1023

int speedValue = 1023;

// ============================================================
// WATCHDOG
// ============================================================

// Robot stops if no valid movement command is received
// for 3 seconds.

const unsigned long COMMAND_TIMEOUT = 1000;

unsigned long lastCommandTime = 0;

// ============================================================
// ROBOT STATE
// ============================================================

char currentCommand = 'S';

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

void webSocketEvent(
  uint8_t num,
  WStype_t type,
  uint8_t *payload,
  size_t length
);

void processCommand(String command);

void moveForward();
void moveBackward();

void turnLeft();
void turnRight();

void forwardRight();
void forwardLeft();

void backwardRight();
void backwardLeft();

void stopRobot();

void setMotor(
  int in1,
  int in2,
  bool forward
);

void setSpeedLevel(int level);

// ============================================================
// SETUP
// ============================================================

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println("========================================");
  Serial.println("      🚀 WIFI ROBOT INITIALIZING");
  Serial.println("========================================");

  // ----------------------------------------------------------
  // MOTOR PINS
  // ----------------------------------------------------------

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // ----------------------------------------------------------
  // PWM
  // ----------------------------------------------------------

  analogWriteRange(MAX_PWM);

  // ----------------------------------------------------------
  // SAFE STARTUP
  // ----------------------------------------------------------

  stopRobot();

  currentCommand = 'S';

  // ----------------------------------------------------------
  // WIFI ACCESS POINT
  // ----------------------------------------------------------

  WiFi.mode(WIFI_AP);

  WiFi.softAP(ssid, password);

  WiFi.setSleepMode(WIFI_NONE_SLEEP);

  Serial.println();
  Serial.println("WiFi Access Point Started");

  Serial.print("SSID: ");
  Serial.println(ssid);

  Serial.print("Password: ");
  Serial.println(password);

  Serial.print("Robot IP: ");
  Serial.println(WiFi.softAPIP());

  // ----------------------------------------------------------
  // WEBSOCKET
  // ----------------------------------------------------------

  webSocket.begin();

  webSocket.onEvent(webSocketEvent);

  // ----------------------------------------------------------
  // WATCHDOG
  // ----------------------------------------------------------

  lastCommandTime = millis();

  Serial.println();
  Serial.println("WebSocket Server Started");
  Serial.println("WebSocket Port: 80");

  Serial.println("Watchdog: ENABLED");
  Serial.println("Timeout: 3 seconds");

  Serial.println();
  Serial.println("========================================");
  Serial.println("          🤖 ROBOT READY");
  Serial.println("========================================");
}

// ============================================================
// LOOP
// ============================================================

void loop() {

  // Process WebSocket communication
  webSocket.loop();

  // ==========================================================
  // COMMAND WATCHDOG
  // ==========================================================

  if (currentCommand != 'S') {

    if (millis() - lastCommandTime >= COMMAND_TIMEOUT) {

      Serial.println();
      Serial.println("⚠ WATCHDOG TIMEOUT");
      Serial.println("No movement command received.");

      stopRobot();

      currentCommand = 'S';

      lastCommandTime = millis();
    }
  }
}

// ============================================================
// WEBSOCKET EVENT
// ============================================================

void webSocketEvent(
  uint8_t num,
  WStype_t type,
  uint8_t *payload,
  size_t length
) {

  // ----------------------------------------------------------
  // CLIENT CONNECTED
  // ----------------------------------------------------------

  if (type == WStype_CONNECTED) {

    Serial.print("📱 Client connected: ");
    Serial.println(num);

    // Always start safely
    stopRobot();

    currentCommand = 'S';

    return;
  }

  // ----------------------------------------------------------
  // CLIENT DISCONNECTED
  // ----------------------------------------------------------

  if (type == WStype_DISCONNECTED) {

    Serial.print("📴 Client disconnected: ");
    Serial.println(num);

    // CRITICAL SAFETY
    stopRobot();

    currentCommand = 'S';

    return;
  }

  // ----------------------------------------------------------
  // TEXT COMMAND
  // ----------------------------------------------------------

if (type == WStype_TEXT) {

  String command = "";

  for (size_t i = 0; i < length; i++) {
    command += (char)payload[i];
  }

  command.trim();

  static unsigned long lastReceivedTime = 0;

  unsigned long now = millis();

  Serial.print("Command received: ");
  Serial.print(command);

  if (lastReceivedTime != 0) {

    Serial.print(" | Interval: ");
    Serial.print(now - lastReceivedTime);
    Serial.println(" ms");

  } else {

    Serial.println();
  }

  lastReceivedTime = now;

  processCommand(command);
}
}

// ============================================================
// COMMAND PROCESSOR
// ============================================================

void processCommand(String command) {

  if (command.length() == 0) {
    return;
  }

  // ----------------------------------------------------------
  // MOVEMENT
  // ----------------------------------------------------------

  if (command == "F") {

    moveForward();
    return;
  }

  if (command == "B") {

    moveBackward();
    return;
  }

  if (command == "L") {

    turnLeft();
    return;
  }

  if (command == "R") {

    turnRight();
    return;
  }

  // ----------------------------------------------------------
  // DIAGONAL
  // ----------------------------------------------------------

  if (command == "E") {

    forwardRight();
    return;
  }

  if (command == "Q") {

    forwardLeft();
    return;
  }

  if (command == "C") {

    backwardRight();
    return;
  }

  if (command == "Z") {

    backwardLeft();
    return;
  }

  // ----------------------------------------------------------
  // STOP
  // ----------------------------------------------------------

  if (command == "S") {

    stopRobot();

    currentCommand = 'S';

    return;
  }

  // ----------------------------------------------------------
  // SPEED
  // ----------------------------------------------------------

  if (command.startsWith("V")) {

    String speedCommand =
      command.substring(1);

    if (speedCommand == "A") {

      speedValue = MAX_PWM;

      Serial.println("Speed: MAX");

      return;
    }

    int level =
      speedCommand.toInt();

    if (level >= 0 && level <= 9) {

      setSpeedLevel(level);

      return;
    }
  }

  // ----------------------------------------------------------
  // FUNCTION BUTTONS
  // ----------------------------------------------------------

  if (command == "H") {

    Serial.println("F1 ON");
    return;
  }

  if (command == "h") {

    Serial.println("F1 OFF");
    return;
  }

  if (command == "K") {

    Serial.println("F2 ON");
    return;
  }

  if (command == "k") {

    Serial.println("F2 OFF");
    return;
  }

  if (command == "T") {

    Serial.println("F3 ON");
    return;
  }

  if (command == "t") {

    Serial.println("F3 OFF");
    return;
  }

  // ----------------------------------------------------------
  // INVALID COMMAND
  // ----------------------------------------------------------

  Serial.print("Unknown command: ");
  Serial.println(command);
}

// ============================================================
// GENERIC MOTOR CONTROL
// ============================================================

void setMotor(
  int in1,
  int in2,
  bool forward
) {

  digitalWrite(in1, forward);
  digitalWrite(in2, !forward);
}

// ============================================================
// FORWARD
// ============================================================

void moveForward() {

  setMotor(IN1, IN2, true);
  setMotor(IN3, IN4, true);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  currentCommand = 'F';

  lastCommandTime = millis();

  Serial.println("➡ FORWARD");
}

// ============================================================
// BACKWARD
// ============================================================

void moveBackward() {

  setMotor(IN1, IN2, false);
  setMotor(IN3, IN4, false);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  currentCommand = 'B';

  lastCommandTime = millis();

  Serial.println("⬅ BACKWARD");
}

// ============================================================
// LEFT
// ============================================================

void turnLeft() {

  setMotor(IN1, IN2, false);
  setMotor(IN3, IN4, true);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  currentCommand = 'L';

  lastCommandTime = millis();

  Serial.println("↩ LEFT");
}

// ============================================================
// RIGHT
// ============================================================

void turnRight() {

  setMotor(IN1, IN2, true);
  setMotor(IN3, IN4, false);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  currentCommand = 'R';

  lastCommandTime = millis();

  Serial.println("↪ RIGHT");
}

// ============================================================
// FORWARD RIGHT
// ============================================================

void forwardRight() {

  // Left motor forward
  setMotor(IN1, IN2, true);

  // Right motor stopped
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, 0);

  currentCommand = 'E';

  lastCommandTime = millis();

  Serial.println("↗ FORWARD RIGHT");
}

// ============================================================
// FORWARD LEFT
// ============================================================

void forwardLeft() {

  // Left motor stopped
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  // Right motor forward
  setMotor(IN3, IN4, true);

  analogWrite(ENA, 0);
  analogWrite(ENB, speedValue);

  currentCommand = 'Q';

  lastCommandTime = millis();

  Serial.println("↖ FORWARD LEFT");
}

// ============================================================
// BACKWARD RIGHT
// ============================================================

void backwardRight() {

  // Left motor backward
  setMotor(IN1, IN2, false);

  // Right motor stopped
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, 0);

  currentCommand = 'C';

  lastCommandTime = millis();

  Serial.println("↘ BACKWARD RIGHT");
}

// ============================================================
// BACKWARD LEFT
// ============================================================

void backwardLeft() {

  // Left motor stopped
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  // Right motor backward
  setMotor(IN3, IN4, false);

  analogWrite(ENA, 0);
  analogWrite(ENB, speedValue);

  currentCommand = 'Z';

  lastCommandTime = millis();

  Serial.println("↙ BACKWARD LEFT");
}

// ============================================================
// STOP
// ============================================================

void stopRobot() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  currentCommand = 'S';

  Serial.println("🛑 STOP");
}

// ============================================================
// SPEED
// ============================================================

void setSpeedLevel(int level) {

  /*
     App:
     V0 = Level 0
     V1 = Level 1
     ...
     V9 = Level 9
     VA = Maximum
  */

  speedValue =
    map(
      level,
      0,
      9,
      0,
      MAX_PWM
    );

  Serial.print("Speed level: ");
  Serial.print(level);

  Serial.print(" | PWM: ");
  Serial.println(speedValue);

  // Update current motor speed if moving
  if (currentCommand != 'S') {

    // Normal full movement
    if (currentCommand == 'F' ||
        currentCommand == 'B' ||
        currentCommand == 'L' ||
        currentCommand == 'R') {

      analogWrite(ENA, speedValue);
      analogWrite(ENB, speedValue);
    }
  }
}
