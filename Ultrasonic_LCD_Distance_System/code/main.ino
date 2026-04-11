/*
  📏 Ultrasonic Distance Measurement System (LCD + Median Filter)

  Features:
  - Accurate distance measurement (HC-SR04)
  - Median filtering for noise reduction
  - Stable LCD display
  - Error handling for no-echo condition

  Author: Venkateswarlu Reddy
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- PINS ----------------
#define TRIG_PIN 6
#define ECHO_PIN 7

// ---------------- PARAMETERS ----------------
#define SAMPLE_SIZE 5
#define UPDATE_DELAY 150

// ---------------- ULTRASONIC READ ----------------
float readDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if(duration == 0) return -1;

  return (duration * 0.0343) / 2.0;
}

// ---------------- MEDIAN FILTER ----------------
float getFilteredDistance()
{
  float values[SAMPLE_SIZE];

  for(int i=0; i<SAMPLE_SIZE; i++)
  {
    values[i] = readDistance();
    delay(10);
  }

  // Bubble sort
  for(int i=0; i<SAMPLE_SIZE-1; i++)
  {
    for(int j=0; j<SAMPLE_SIZE-i-1; j++)
    {
      if(values[j] > values[j+1])
      {
        float temp = values[j];
        values[j] = values[j+1];
        values[j+1] = temp;
      }
    }
  }

  return values[SAMPLE_SIZE/2];
}

// ---------------- SETUP ----------------
void setup()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Ultrasonic Ready");
  delay(1500);
  lcd.clear();
}

// ---------------- LOOP ----------------
void loop()
{
  float distance = getFilteredDistance();

  lcd.setCursor(0,0);
  lcd.print("Distance:");

  lcd.setCursor(0,1);

  if(distance < 0)
  {
    lcd.print("No Signal      ");
  }
  else
  {
    char buffer[10];
    dtostrf(distance, 6, 2, buffer);

    lcd.print(buffer);
    lcd.print(" cm   ");
  }

  delay(UPDATE_DELAY);
}
