/*
   ============================================================
              4-WHEEL DIGITAL LIGHT FOLLOWER
   ============================================================

   Arduino UNO
   LM393 Light Sensors
   L298N Motor Driver
   4-Wheel Differential Drive

   SENSOR:
   LEFT  -> D12
   RIGHT -> D10

   MOTOR DRIVER:
   ENA -> D3
   ENB -> D9

   IN1 -> D4
   IN2 -> D5

   IN3 -> D6
   IN4 -> D7

   LOGIC:

   BOTH LIGHT  -> FORWARD
   LEFT LIGHT  -> LEFT
   RIGHT LIGHT -> RIGHT
   NO LIGHT    -> STOP

   IMPORTANT:
   ENA controls LEFT SIDE motors
   ENB controls RIGHT SIDE motors

   So if you have 4 motors:

   LEFT FRONT  + LEFT REAR  -> ENA / IN1 / IN2
   RIGHT FRONT + RIGHT REAR -> ENB / IN3 / IN4
*/


// ============================================================
//                       SENSOR PINS
// ============================================================

#define LDR_LEFT   12
#define LDR_RIGHT  10


// ============================================================
//                       MOTOR PINS
// ============================================================

#define ENA 3
#define ENB 9

#define IN1 4
#define IN2 5

#define IN3 6
#define IN4 7


// ============================================================
//                       SPEED SETTINGS
// ============================================================

int baseSpeed = 160;

int turnSpeed = 180;

int slowSpeed = 70;

int maxSpeed = 220;


// ============================================================
//                       PID SETTINGS
// ============================================================

float Kp = 35.0;
float Ki = 0.0;
float Kd = 15.0;

int error = 0;
int previousError = 0;

float integral = 0;

float correction = 0;


// ============================================================
//                           SETUP
// ============================================================

void setup() {

  // Sensors
  pinMode(LDR_LEFT, INPUT);
  pinMode(LDR_RIGHT, INPUT);

  // Motor enable pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Motor direction pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);

  stopBot();

  Serial.println();
  Serial.println("==============================");
  Serial.println(" 4-WHEEL LIGHT FOLLOWER");
  Serial.println("==============================");
}


// ============================================================
//                            LOOP
// ============================================================

void loop() {

  // Read sensors

  int leftSensor = digitalRead(LDR_LEFT);
  int rightSensor = digitalRead(LDR_RIGHT);


  /*
     LM393 normally gives:

     LOW  = light detected
     HIGH = no light

     If your sensor works opposite,
     change LOW to HIGH.
  */

  bool leftLight = (leftSensor == LOW);
  bool rightLight = (rightSensor == LOW);


  // ==========================================================
  //                    BOTH DETECT LIGHT
  // ==========================================================

  if (leftLight && rightLight) {

    error = 0;

    integral += error;

    integral = constrain(integral, -20, 20);

    int derivative = error - previousError;

    correction =
      (Kp * error) +
      (Ki * integral) +
      (Kd * derivative);

    previousError = error;


    int leftSpeed =
      baseSpeed + correction;

    int rightSpeed =
      baseSpeed - correction;


    leftSpeed =
      constrain(leftSpeed, 0, maxSpeed);

    rightSpeed =
      constrain(rightSpeed, 0, maxSpeed);


    moveForward(leftSpeed, rightSpeed);

    Serial.println("FORWARD");
  }


  // ==========================================================
  //                    LEFT SENSOR ONLY
  // ==========================================================

  else if (leftLight && !rightLight) {

    error = -1;

    integral += error;

    integral = constrain(integral, -20, 20);

    int derivative = error - previousError;

    correction =
      (Kp * error) +
      (Ki * integral) +
      (Kd * derivative);

    previousError = error;


    /*
       PROPER 4-WHEEL LEFT TURN

       LEFT SIDE:
       Both left wheels move backward slowly

       RIGHT SIDE:
       Both right wheels move forward

       Therefore ALL FOUR WHEELS rotate.
    */

    turnLeft();

    Serial.println("LEFT - 4 WHEELS");
  }


  // ==========================================================
  //                    RIGHT SENSOR ONLY
  // ==========================================================

  else if (!leftLight && rightLight) {

    error = 1;

    integral += error;

    integral = constrain(integral, -20, 20);

    int derivative = error - previousError;

    correction =
      (Kp * error) +
      (Kd * derivative) +
      (Ki * integral);

    previousError = error;


    /*
       PROPER 4-WHEEL RIGHT TURN

       LEFT SIDE:
       Both left wheels move forward

       RIGHT SIDE:
       Both right wheels move backward slowly

       ALL FOUR WHEELS ROTATE.
    */

    turnRight();

    Serial.println("RIGHT - 4 WHEELS");
  }


  // ==========================================================
  //                     NO LIGHT
  // ==========================================================

  else {

    integral = 0;

    stopBot();

    Serial.println("STOP");
  }


  delay(15);
}


// ============================================================
//                    FORWARD - 4 WHEELS
// ============================================================

void moveForward(int leftSpeed, int rightSpeed) {

  // ---------------- LEFT SIDE ----------------

  // Left front + left rear
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENA, leftSpeed);


  // ---------------- RIGHT SIDE ----------------

  // Right front + right rear
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENB, rightSpeed);
}


// ============================================================
//                    LEFT TURN - 4 WHEELS
// ============================================================

void turnLeft() {

  /*
       LEFT SIDE
       Both wheels BACKWARD

             ← LEFT FRONT
             ← LEFT REAR


       RIGHT SIDE
       Both wheels FORWARD

             → RIGHT FRONT
             → RIGHT REAR

       Robot rotates LEFT.
  */


  // LEFT TWO WHEELS BACKWARD

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENA, turnSpeed);


  // RIGHT TWO WHEELS FORWARD

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENB, turnSpeed);
}


// ============================================================
//                    RIGHT TURN - 4 WHEELS
// ============================================================

void turnRight() {

  /*
       LEFT SIDE
       Both wheels FORWARD

             → LEFT FRONT
             → LEFT REAR


       RIGHT SIDE
       Both wheels BACKWARD

             ← RIGHT FRONT
             ← RIGHT REAR

       Robot rotates RIGHT.
  */


  // LEFT TWO WHEELS FORWARD

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENA, turnSpeed);


  // RIGHT TWO WHEELS BACKWARD

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENB, turnSpeed);
}


// ============================================================
//                         STOP
// ============================================================

void stopBot() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);


  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
