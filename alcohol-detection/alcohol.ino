/*
  🚗 Smart Alcohol Detection & Safety System (Top 1%)

  Features:
  - Real-time alcohol detection (MQ3)
  - Moving average filtering
  - Non-blocking architecture
  - State-based control system
  - Motor safety shutdown
  - LCD status display
  - Audible alert system

  Author: Venkateswarlu Reddy
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- PINS ----------------
#define MQ3_PIN A0
#define BUZZER 8

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

// ---------------- PARAMETERS ----------------
#define THRESHOLD 400
#define SAMPLE_INTERVAL 100
#define DISPLAY_INTERVAL 500
#define ALERT_BUZZ_TIME 2000

// ---------------- FILTER ----------------
#define SAMPLE_SIZE 10
int samples[SAMPLE_SIZE];
int index = 0;
long total = 0;

// ---------------- TIMERS ----------------
unsigned long lastSampleTime = 0;
unsigned long lastDisplayTime = 0;
unsigned long alertStartTime = 0;

// ---------------- STATE ----------------
bool alertState = false;

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(9600);

  pinMode(BUZZER, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  lcd.begin(16,2);
  lcd.backlight();

  lcd.print("Alcohol System");
  delay(1000);
  lcd.clear();

  // Initialize filter
  for(int i=0;i<SAMPLE_SIZE;i++) samples[i]=0;
}

// ---------------- LOOP ----------------
void loop() {

  unsigned long now = millis();

  // -------- SENSOR SAMPLING --------
  if(now - lastSampleTime >= SAMPLE_INTERVAL){

    int value = analogRead(MQ3_PIN);

    total -= samples[index];
    samples[index] = value;
    total += value;

    index = (index + 1) % SAMPLE_SIZE;

    lastSampleTime = now;
  }

  int avgValue = total / SAMPLE_SIZE;

  // -------- DECISION --------
  if(avgValue > THRESHOLD){
    if(!alertState){
      alertState = true;
      alertStartTime = now;
      stopMotors();
      digitalWrite(BUZZER, HIGH);
      Serial.println("ALCOHOL DETECTED!");
    }
  } else {
    if(alertState){
      alertState = false;
      digitalWrite(BUZZER, LOW);
      Serial.println("SAFE STATE");
    }
    moveForward();
  }

  // -------- BUZZER AUTO OFF --------
  if(alertState && (now - alertStartTime > ALERT_BUZZ_TIME)){
    digitalWrite(BUZZER, LOW);
  }

  // -------- DISPLAY UPDATE --------
  if(now - lastDisplayTime >= DISPLAY_INTERVAL){

    lcd.setCursor(0,0);
    lcd.print("Value:");
    lcd.print(avgValue);
    lcd.print("   ");

    lcd.setCursor(0,1);

    if(alertState){
      lcd.print("ALCOHOL ALERT!");
    } else {
      lcd.print("SAFE           ");
    }

    lastDisplayTime = now;
  }
}

// ---------------- MOTOR CONTROL ----------------
void moveForward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
