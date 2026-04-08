/*
  🚀 WiFi Controlled Robot (ESP8266)

  Features:
  - Mobile app control (MIT App Inventor)
  - Clean command handling
  - Modular motor control
  - Expandable architecture

  Author: Venkateswarlu Reddy
*/

#include <ESP8266WiFi.h>

// -------- WIFI CREDENTIALS --------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_PASSWORD";

WiFiServer server(80);

// -------- MOTOR PINS --------
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4

// -------- FUNCTION DECLARATIONS --------
void stopRobot();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void handleCommand(String cmd);

// -------- SETUP --------
void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopRobot();

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  server.begin();
}

// -------- LOOP --------
void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  Serial.println(request);

  // Extract command
  if (request.indexOf("/forward") != -1) handleCommand("F");
  else if (request.indexOf("/back") != -1) handleCommand("B");
  else if (request.indexOf("/left") != -1) handleCommand("L");
  else if (request.indexOf("/right") != -1) handleCommand("R");
  else if (request.indexOf("/stop") != -1) handleCommand("S");

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/plain");
  client.println("Connection: close");
  client.println();
  client.println("OK");
}

// -------- COMMAND HANDLER --------
void handleCommand(String cmd) {
  if (cmd == "F") moveForward();
  else if (cmd == "B") moveBackward();
  else if (cmd == "L") turnLeft();
  else if (cmd == "R") turnRight();
  else if (cmd == "S") stopRobot();
}

// -------- MOTOR FUNCTIONS --------

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
