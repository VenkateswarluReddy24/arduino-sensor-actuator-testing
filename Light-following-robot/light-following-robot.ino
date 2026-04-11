/*
  🤖 Digital PID Light Following Robot (Top 1%)

  Features:
  - LM393 digital light sensing
  - PID-based smooth correction
  - Stable motor control
  - Proper edge-case handling

  Author: Venkateswarlu Reddy
*/

// ---------------- SENSOR PINS ----------------
#define LDR_LEFT   2
#define LDR_RIGHT  12

// ---------------- MOTOR DRIVER ----------------
#define ENA 6
#define ENB 5
#define IN1 10
#define IN2 9
#define IN3 8
#define IN4 7

// ---------------- PARAMETERS ----------------
int baseSpeed = 120;

// PID Tuning
float Kp = 15;
float Kd = 8;
float Ki = 0;

int error = 0;
int previousError = 0;
int integral = 0;
int correction = 0;

// ---------------- SETUP ----------------
void setup() {

  pinMode(LDR_LEFT, INPUT);
  pinMode(LDR_RIGHT, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  Serial.println("LIGHT FOLLOWER STARTED");
}

// ---------------- LOOP ----------------
void loop() {

  int leftVal  = digitalRead(LDR_LEFT);
  int rightVal = digitalRead(LDR_RIGHT);

  bool leftLight  = (leftVal == LOW);
  bool rightLight = (rightVal == LOW);

  // -------- ERROR CALCULATION --------
  if(leftLight && rightLight)
    error = 0;       // straight

  else if(leftLight && !rightLight)
    error = -1;      // turn left

  else if(!leftLight && rightLight)
    error = +1;      // turn right

  else
  {
    stopBot();       // no light detected
    return;
  }

  // -------- PID CONTROL --------
  integral += error;
  int derivative = error - previousError;

  correction = (Kp * error) + (Kd * derivative) + (Ki * integral);

  previousError = error;

  int leftSpeed  = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  // Safety limits
  leftSpeed  = constrain(leftSpeed, 80, 200);
  rightSpeed = constrain(rightSpeed, 80, 200);

  moveForward(leftSpeed, rightSpeed);

  // Debug
  Serial.print("Error: "); Serial.print(error);
  Serial.print("  L: "); Serial.print(leftSpeed);
  Serial.print("  R: "); Serial.println(rightSpeed);

  delay(20);
}

// ---------------- MOTOR CONTROL ----------------
void moveForward(int leftSpeed, int rightSpeed) {

  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopBot() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
