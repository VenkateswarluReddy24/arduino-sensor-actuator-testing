/*
  🌱 Smart Plant Health Monitoring System (Emotion-Based)

  Features:
  - Capacitive soil moisture sensing
  - Temperature monitoring (DHT11)
  - Ambient light detection (LDR)
  - LED Matrix emoji feedback
  - LCD status display
  - Intelligent plant “emotion engine”

  Author: Venkateswarlu Reddy
*/

#include <LedControl.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ================= LCD =================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================= MATRIX =================
#define DIN 11
#define CLK 13
#define CS  10
LedControl matrix = LedControl(DIN, CLK, CS, 1);

// ================= SENSOR PINS =================
#define SOIL_PIN A0
#define LDR_PIN  5
#define DHTPIN   9
#define DHTTYPE  DHT11

DHT dht(DHTPIN, DHTTYPE);

// ================= SYSTEM STATES =================
enum PlantState {
  HEALTHY,
  DRY,
  HOT,
  SLEEP
};

PlantState currentState = HEALTHY;
unsigned long stateTimer = 0;

// ================= GLOBAL VARIABLES =================
String moistureLevel = "Moist";
String statusText = "Healthy";

// ================= EMOJIS =================
byte HAPPY[8] = {
  B00111100,B01000010,B10100101,B10000001,
  B10100101,B10011001,B01000010,B00111100
};

byte SAD[8] = {
  B00111100,B01000010,B10100101,B10000001,
  B10011001,B10100101,B01000010,B00111100
};

byte HOT[8] = {
  B00111100,B01000010,B10111101,B10000001,
  B10111101,B10011001,B01000010,B00111100
};

byte SLEEPY[8] = {
  B00111100,B01000010,B10111101,B10000001,
  B10000001,B10111101,B01000010,B00111100
};

// ================= DISPLAY =================
void showEmoji(byte emoji[]) {
  for (int i = 0; i < 8; i++) {
    matrix.setColumn(0, i, emoji[i]);
  }
}

// ================= SENSOR READ =================
int readSoil() {
  return analogRead(SOIL_PIN);
}

float readTemperature() {
  float t = dht.readTemperature();
  if (isnan(t)) return -1;
  return t;
}

bool isDark() {
  return digitalRead(LDR_PIN) == HIGH;
}

// ================= EMOTION ENGINE =================
void updateEmotion(int soil, float temp, bool dark)
{
  PlantState newState = currentState;

  // -------- SOIL LOGIC --------
  if (soil > 600) {
    moistureLevel = "Very Dry";
    statusText = "Water Needed";
    newState = DRY;
  }
  else if (soil > 520) {
    moistureLevel = "Dry";
    statusText = "Water Soon";
    newState = DRY;
  }
  else if (soil < 350) {
    moistureLevel = "Wet";
    statusText = "Healthy";
    newState = HEALTHY;
  }
  else {
    moistureLevel = "Moist";
    statusText = "Healthy";
    newState = HEALTHY;
  }

  // -------- TEMPERATURE PRIORITY --------
  if (temp > 35) {
    newState = HOT;
    statusText = "Heat Stress";
  }

  // -------- NIGHT MODE --------
  if (dark && newState == HEALTHY) {
    newState = SLEEP;
    statusText = "Sleeping";
  }

  // -------- STATE STABILITY --------
  if (newState != currentState && millis() - stateTimer > 3000) {
    currentState = newState;
    stateTimer = millis();
  }

  // -------- EMOJI OUTPUT --------
  switch (currentState) {
    case HEALTHY: showEmoji(HAPPY); break;
    case DRY:     showEmoji(SAD); break;
    case HOT:     showEmoji(HOT); break;
    case SLEEP:   showEmoji(SLEEPY); break;
  }
}

// ================= LCD =================
void updateLCD(int soil, float temp)
{
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print((int)temp);
  lcd.print("C S:");
  lcd.print(soil);
  lcd.print("   ");

  lcd.setCursor(0,1);
  lcd.print(moistureLevel);
  lcd.print(" ");
  lcd.print(statusText);
  lcd.print("   ");
}

// ================= SETUP =================
void setup()
{
  pinMode(LDR_PIN, INPUT);

  matrix.shutdown(0, false);
  matrix.setIntensity(0, 8);
  matrix.clearDisplay(0);

  lcd.init();
  lcd.backlight();

  dht.begin();

  lcd.setCursor(0,0);
  lcd.print("Smart Plant AI");
  lcd.setCursor(0,1);
  lcd.print("System Booting");
  delay(2000);
  lcd.clear();
}

// ================= LOOP =================
void loop()
{
  int soil = readSoil();
  float temp = readTemperature();
  bool dark = isDark();

  updateEmotion(soil, temp, dark);
  updateLCD(soil, temp);

  delay(500);
}
