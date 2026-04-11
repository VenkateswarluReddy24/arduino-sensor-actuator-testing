/*
  🌈 RGB LED Control System (PWM Based)

  Features:
  - Modular RGB control function
  - Smooth color transitions
  - Clean and scalable structure
  - PWM-based brightness control

  Author: Venkateswarlu Reddy
*/

// ---------------- PINS ----------------
#define RED_PIN   9
#define GREEN_PIN 10
#define BLUE_PIN  11

// ---------------- FUNCTION ----------------
void setColor(int r, int g, int b)
{
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

// ---------------- SETUP ----------------
void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

// ---------------- LOOP ----------------
void loop()
{
  // Basic Colors
  setColor(255, 0, 0);   // Red
  delay(1000);

  setColor(0, 255, 0);   // Green
  delay(1000);

  setColor(0, 0, 255);   // Blue
  delay(1000);

  setColor(255, 255, 255); // White
  delay(1000);

  // Smooth Transition Demo
  fadeColors();
}

// ---------------- SMOOTH TRANSITION ----------------
void fadeColors()
{
  // Red → Green
  for(int i = 0; i <= 255; i++)
  {
    setColor(255 - i, i, 0);
    delay(5);
  }

  // Green → Blue
  for(int i = 0; i <= 255; i++)
  {
    setColor(0, 255 - i, i);
    delay(5);
  }

  // Blue → Red
  for(int i = 0; i <= 255; i++)
  {
    setColor(i, 0, 255 - i);
    delay(5);
  }
}
