/*
  🔐 Smart Touch-Based Security System (Pattern Authentication)

  Features:
  - Touch pattern-based authentication
  - Timing-based security validation
  - Intruder detection system
  - Servo-based smart lock
  - LCD feedback system
  - Buzzer alert system

  Author: Venkateswarlu Reddy
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// ---------------- PINS ----------------
#define TOUCH_PIN   2
#define BUZZER_PIN  8
#define SERVO_PIN   10

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo doorServo;

// ---------------- SERVO ----------------
#define LOCK_POS 0
#define OPEN_POS 90

// ---------------- TIMING ----------------
#define MIN_PAUSE 600
#define MAX_PAUSE 2500
#define TIMEOUT   5000
#define DEBOUNCE  200

// ---------------- SECURITY ----------------
#define MAX_ATTEMPTS 3
int wrongAttempts = 0;

// ---------------- STATE ----------------
enum SystemState {
  WAIT_START,
  WAIT_SECOND_TOUCH
};

SystemState systemState = WAIT_START;

unsigned long lastTouchTime = 0;

// ---------------- TOUCH FILTER ----------------
#define TOUCH_STABLE_COUNT 5
int touchCounter = 0;
bool stableTouch = false;

// ================= SETUP =================
void setup()
{
  pinMode(TOUCH_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  doorServo.attach(SERVO_PIN);
  doorServo.write(LOCK_POS);
  delay(500);
  doorServo.detach();

  lcd.print("SMART SECURITY");
  lcd.setCursor(0,1);
  lcd.print("System Ready");
  delay(2000);

  resetSystem();
}

// ================= LOOP =================
void loop()
{
  bool touch = digitalRead(TOUCH_PIN);

  // -------- TOUCH FILTER --------
  if (touch)
  {
    touchCounter++;

    if (touchCounter >= TOUCH_STABLE_COUNT && !stableTouch)
    {
      stableTouch = true;
      handleTouch();
    }
  }
  else
  {
    touchCounter = 0;
    stableTouch = false;
  }

  // -------- TIMEOUT --------
  if (systemState == WAIT_SECOND_TOUCH &&
      millis() - lastTouchTime > TIMEOUT)
  {
    lcd.clear();
    lcd.print("Session Timeout");
    delay(1200);
    resetSystem();
  }
}

// ================= TOUCH HANDLER =================
void handleTouch()
{
  delay(DEBOUNCE);

  unsigned long now = millis();

  switch(systemState)
  {
    case WAIT_START:

      systemState = WAIT_SECOND_TOUCH;
      lastTouchTime = now;

      lcd.clear();
      lcd.print("Touch 1 OK");

      beepShort();
      break;

    case WAIT_SECOND_TOUCH:

      verifyPattern(now - lastTouchTime);
      break;
  }
}

// ================= VERIFY =================
void verifyPattern(unsigned long pause)
{
  lcd.clear();
  lcd.print("Verifying...");
  delay(400);

  if (pause >= MIN_PAUSE && pause <= MAX_PAUSE)
  {
    wrongAttempts = 0;
    grantAccess();
  }
  else
  {
    wrongAttempts++;

    lcd.clear();
    lcd.print("Wrong Pattern!");
    beepLong();

    if (wrongAttempts >= MAX_ATTEMPTS)
    {
      intruderAlert();
    }

    resetSystem();
  }
}

// ================= ACCESS =================
void grantAccess()
{
  lcd.clear();
  lcd.print("ACCESS GRANTED");

  for(int i=0;i<2;i++){
    beepShort();
    delay(150);
  }

  doorServo.attach(SERVO_PIN);

  // OPEN
  for(int pos = LOCK_POS; pos <= OPEN_POS; pos++)
  {
    doorServo.write(pos);
    delay(15);
  }

  lcd.setCursor(0,1);
  lcd.print("Door Open");

  delay(5000);

  // CLOSE
  for(int pos = OPEN_POS; pos >= LOCK_POS; pos--)
  {
    doorServo.write(pos);
    delay(15);
  }

  doorServo.detach();

  lcd.clear();
  lcd.print("Door Locked");

  delay(1500);

  resetSystem();
}

// ================= INTRUDER =================
void intruderAlert()
{
  lcd.clear();
  lcd.print("INTRUDER ALERT!");
  lcd.setCursor(0,1);
  lcd.print("System Locked");

  for(int i=0;i<10;i++){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(250);
    digitalWrite(BUZZER_PIN, LOW);
    delay(250);
  }

  delay(8000);
  wrongAttempts = 0;
}

// ================= BUZZER =================
void beepShort()
{
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}

void beepLong()
{
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1500);
  digitalWrite(BUZZER_PIN, LOW);
}

// ================= RESET =================
void resetSystem()
{
  systemState = WAIT_START;

  lcd.clear();
  lcd.print("Touch to Begin");
}
