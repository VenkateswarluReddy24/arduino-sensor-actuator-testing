/*
  🎨 Color Detection System (TCS3200 + LCD + RGB LED)

  Features:
  - Detects RED, GREEN, BLUE, WHITE
  - LCD output display
  - RGB LED indication
  - Stable color detection logic

  Author: Venkateswarlu Reddy
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- TCS3200 ----------------
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define SENSOR_OUT 2
#define OE 8

// ---------------- RGB LED ----------------
#define RED_LED   9
#define GREEN_LED 11
#define BLUE_LED  10

unsigned long R, G, B;

// ---------------- PARAMETERS ----------------
#define CLOSE_MARGIN   12
#define WHITE_LEVEL    65
#define COLOR_MARGIN   15
#define NO_OBJECT_MIN  90

// ---------------- FUNCTION: SET COLOR ----------------
void setColor(int r, int g, int b) {
  analogWrite(RED_LED, r);
  analogWrite(GREEN_LED, g);
  analogWrite(BLUE_LED, b);
}

// ---------------- FUNCTION: READ COLOR ----------------
void readColor() {

  // RED
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  R = pulseIn(SENSOR_OUT, LOW);

  // GREEN
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  G = pulseIn(SENSOR_OUT, LOW);

  // BLUE
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  B = pulseIn(SENSOR_OUT, LOW);
}

// ---------------- SETUP ----------------
void setup() {

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SENSOR_OUT, INPUT);
  pinMode(OE, OUTPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(OE, LOW);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Color Detector");
  delay(2000);
  lcd.clear();
}

// ---------------- LOOP ----------------
void loop() {

  readColor();

  unsigned long maxVal = max(R, max(G, B));
  unsigned long minVal = min(R, min(G, B));
  unsigned long avgVal = (R + G + B) / 3;

  String detectedColor = "UNKNOWN";

  // -------- WHITE --------
  if ((maxVal - minVal) < CLOSE_MARGIN && avgVal < WHITE_LEVEL) {
    detectedColor = "WHITE";
    setColor(255,255,255);
  }

  // -------- NO OBJECT --------
  else if (minVal > NO_OBJECT_MIN) {
    detectedColor = "NO OBJECT";
    setColor(0,0,0);
  }

  // -------- RED --------
  else if (R < G && R < B && (G - R) > COLOR_MARGIN && (B - R) > COLOR_MARGIN) {
    detectedColor = "RED";
    setColor(255,0,0);
  }

  // -------- GREEN --------
  else if (G < R && G < B && (R - G) > COLOR_MARGIN && (B - G) > COLOR_MARGIN) {
    detectedColor = "GREEN";
    setColor(0,255,0);
  }

  // -------- BLUE --------
  else if (B < R && B < G && (R - B) > COLOR_MARGIN && (G - B) > COLOR_MARGIN) {
    detectedColor = "BLUE";
    setColor(0,0,255);
  }

  else {
    setColor(0,0,0);
  }

  // -------- LCD DISPLAY --------
  lcd.setCursor(0,0);
  lcd.print("Detected:      ");

  lcd.setCursor(0,1);
  lcd.print(detectedColor);
  lcd.print("      ");

  delay(300);
}
