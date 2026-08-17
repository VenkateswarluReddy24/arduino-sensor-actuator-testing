#include <IRremote.hpp>

// =====================================================
// PIN CONFIGURATION
// =====================================================

#define IR_PIN 2

#define ENA 3
#define ENB 9

#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

#define LED_PIN 13

// =====================================================
// IR REMOTE COMMANDS
// =====================================================

#define CMD_1       0x45
#define CMD_2       0x46
#define CMD_3       0x47
#define CMD_4       0x44
#define CMD_5       0x40
#define CMD_6       0x43
#define CMD_7       0x07
#define CMD_8       0x15
#define CMD_9       0x09
#define CMD_0       0x19

#define CMD_STAR    0x16
#define CMD_HASH    0x0D

#define CMD_FORWARD 0x18
#define CMD_BACK    0x52
#define CMD_RIGHT   0x5A
#define CMD_LEFT    0x08
#define CMD_OK      0x1C

// =====================================================
// DEMO SETTINGS
// =====================================================

const unsigned long MOVE_TIME = 500;
const unsigned long ROTATION_TIME = 800;
const unsigned long PWM_PERIOD = 2000;

byte speedLevel = 5;
byte pwmValue = 155;

// =====================================================
// SPEED CONTROL
// =====================================================

void SetSpeed(byte level)
{
  speedLevel = level;

  switch (level)
  {
    case 1: pwmValue = 60;  break;
    case 2: pwmValue = 80;  break;
    case 3: pwmValue = 105; break;
    case 4: pwmValue = 130; break;
    case 5: pwmValue = 155; break;
    case 6: pwmValue = 180; break;
    case 7: pwmValue = 205; break;
    case 8: pwmValue = 230; break;
    case 9: pwmValue = 255; break;
  }

  Serial.print("SPEED LEVEL = ");
  Serial.print(speedLevel);
  Serial.print(" | PWM = ");
  Serial.println(pwmValue);
}

// =====================================================
// STOP
// =====================================================

void StopCar()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  digitalWrite(LED_PIN, HIGH);
}

// =====================================================
// SOFTWARE PWM
// Avoids analogWrite() on D3 because IRremote uses Timer2
// on Arduino Uno.
// =====================================================

void RunMotors(unsigned long runTime)
{
  unsigned long startTime = micros();

  while (micros() - startTime < (runTime * 1000UL))
  {
    unsigned long pwmTime = micros() % PWM_PERIOD;
    unsigned long onTime = ((unsigned long)pwmValue * PWM_PERIOD) / 255UL;

    if (pwmTime < onTime)
    {
      digitalWrite(ENA, HIGH);
      digitalWrite(ENB, HIGH);
    }
    else
    {
      digitalWrite(ENA, LOW);
      digitalWrite(ENB, LOW);
    }
  }

  StopCar();
}

// =====================================================
// MOVEMENT
// =====================================================

void Forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.print("FORWARD | SPEED ");
  Serial.println(speedLevel);

  RunMotors(MOVE_TIME);
}

void Backward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(LED_PIN, LOW);

  Serial.print("BACKWARD | SPEED ");
  Serial.println(speedLevel);

  RunMotors(MOVE_TIME);
}

void Left()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(LED_PIN, LOW);

  Serial.print("LEFT | SPEED ");
  Serial.println(speedLevel);

  RunMotors(MOVE_TIME);
}

void Right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.print("RIGHT | SPEED ");
  Serial.println(speedLevel);

  RunMotors(MOVE_TIME);
}

// =====================================================
// ONE-TIME 360 DEGREE DEMO SPIN
// Calibration may be required for your chassis.
// =====================================================

void Rotate360()
{
  Serial.println("360 DEGREE ROTATION");

  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  digitalWrite(LED_PIN, LOW);

  RunMotors(ROTATION_TIME);

  StopCar();

  Serial.println("ROTATION COMPLETE");
}

// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  StopCar();
  SetSpeed(5);

  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  Serial.println();
  Serial.println("==============================");
  Serial.println("   IR REMOTE ROBOT CAR");
  Serial.println("      STEM DEMO MODE");
  Serial.println("==============================");
  Serial.println("1-9 : SPEED LEVEL");
  Serial.println("UP  : FORWARD");
  Serial.println("DOWN: BACKWARD");
  Serial.println("LEFT: LEFT");
  Serial.println("RIGHT: RIGHT");
  Serial.println("0   : STOP");
  Serial.println("*   : EMERGENCY STOP");
  Serial.println("OK  : 360 DEGREE ROTATION");
  Serial.println("#   : RESET SPEED");
  Serial.println("==============================");
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop()
{
  if (IrReceiver.decode())
  {
    uint16_t command = IrReceiver.decodedIRData.command;
    bool repeat = (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT);

    IrReceiver.resume();

    if (repeat)
    {
      Serial.println("Repeat ignored");
      return;
    }

    Serial.print("Command = 0x");
    if (command < 0x10)
      Serial.print("0");
    Serial.println(command, HEX);

    if (command == CMD_1) SetSpeed(1);
    else if (command == CMD_2) SetSpeed(2);
    else if (command == CMD_3) SetSpeed(3);
    else if (command == CMD_4) SetSpeed(4);
    else if (command == CMD_5) SetSpeed(5);
    else if (command == CMD_6) SetSpeed(6);
    else if (command == CMD_7) SetSpeed(7);
    else if (command == CMD_8) SetSpeed(8);
    else if (command == CMD_9) SetSpeed(9);

    else if (command == CMD_0)
    {
      Serial.println("STOP");
      StopCar();
    }
    else if (command == CMD_STAR)
    {
      Serial.println("EMERGENCY STOP");
      StopCar();
    }
    else if (command == CMD_OK)
    {
      Rotate360();
    }

    else if (command == CMD_FORWARD) Forward();
    else if (command == CMD_BACK) Backward();
    else if (command == CMD_LEFT) Left();
    else if (command == CMD_RIGHT) Right();

    else if (command == CMD_HASH)
    {
      SetSpeed(5);
      Serial.println("SPEED RESET -> LEVEL 5");
    }
    else
    {
      Serial.println("UNKNOWN COMMAND");
    }
  }
}
