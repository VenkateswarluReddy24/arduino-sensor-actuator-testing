/*
  📡 Signal Detection System (Frequency Tuner Simulator)

  Features:
  - Analog frequency tuning using potentiometer
  - Target frequency detection
  - Visual (LCD + LED) and audio feedback
  - Stable, non-flickering display

  Author: Venkateswarlu Reddy
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- PINS ----------------
#define POT_PIN A0
#define BUZZER_PIN 5
#define LED_PIN 3

// ---------------- PARAMETERS ----------------
float frequency = 0;
const float TARGET_FREQ = 100.0;

unsigned long lastUpdate = 0;
#define UPDATE_INTERVAL 200

// ---------------- SETUP ----------------
void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  lcd.setCursor(0,0);
  lcd.print("Signal Scanner");
  delay(1500);
  lcd.clear();
}

// ---------------- LOOP ----------------
void loop() {

  if (millis() - lastUpdate < UPDATE_INTERVAL) return;
  lastUpdate = millis();

  int value = analogRead(POT_PIN);

  // Map to frequency range
  frequency = map(value, 0, 1023, 880, 1080) / 10.0;

  float diff = abs(frequency - TARGET_FREQ);

  // -------- DISPLAY --------
  lcd.setCursor(0,0);
  lcd.print("Freq:");
  lcd.print(frequency);
  lcd.print("   ");

  lcd.setCursor(0,1);

  // -------- LOGIC --------

  // 🎯 PERFECT MATCH
  if (diff < 1.0) {

    lcd.print("Signal Found  ");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1200);
  }

  // 🔍 NEAR SIGNAL
  else if (diff < 5.0) {

    lcd.print("Searching...  ");

    digitalWrite(LED_PIN, millis() % 400 < 200);
    tone(BUZZER_PIN, 900);
  }

  // ❌ NO SIGNAL
  else {

    lcd.print("No Signal     ");
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }
}
