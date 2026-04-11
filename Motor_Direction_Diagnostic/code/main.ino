/*
  🔧 Motor Direction Diagnostic Tool (L298N + Arduino)

  Purpose:
  - Verify motor wiring
  - Validate direction control
  - Test forward, reverse, and turning

  Author: Venkateswarlu Reddy
*/

// ---------------- MOTOR DRIVER ----------------
#define ENA 6
#define ENB 5

#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10

#define TEST_DELAY 3000
#define STOP_DELAY 2000

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set test speed
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  Serial.println("=================================");
  Serial.println(" MOTOR DIAGNOSTIC STARTED ");
  Serial.println("=================================");
}

// ---------------- LOOP ----------------
void loop() {

  testForward();
  testStop();

  testReverse();
  testStop();

  testLeft();
  testStop();

  testRight();
  testStop();
}

// ---------------- TEST FUNCTIONS ----------------

void testForward() {
  Serial.println("[TEST] FORWARD");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(TEST_DELAY);
}

void testReverse() {
  Serial.println("[TEST] REVERSE");

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(TEST_DELAY);
}

void testLeft() {
  Serial.println("[TEST] TURN LEFT");

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(TEST_DELAY);
}

void testRight() {
  Serial.println("[TEST] TURN RIGHT");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(TEST_DELAY);
}

void testStop() {
  Serial.println("[TEST] STOP");

  stopMotors();
  delay(STOP_DELAY);
}

// ---------------- STOP ----------------
void stopMotors() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
