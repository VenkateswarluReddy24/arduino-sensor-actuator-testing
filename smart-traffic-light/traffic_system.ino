/*
  🚦 Smart Traffic Light System (Dual Road Controller)

  Features:
  - Modular traffic control logic
  - Scalable design (multi-road support)
  - Structured state management
  - TM1637 countdown display

  Author: Venkateswarlu Reddy
*/

#include <TM1637Display.h>

// ---------------- DISPLAY ----------------
#define CLK 2
#define DIO 4
TM1637Display display(CLK, DIO);

// ---------------- TRAFFIC LIGHT STRUCT ----------------
struct TrafficLight {
  int red;
  int yellow;
  int green;
};

// Road configurations
TrafficLight road1 = {10, 13, 12};
TrafficLight road2 = {6, 3, 9};

// ---------------- TIMINGS ----------------
#define GREEN_TIME   15
#define YELLOW_TIME  5
#define RED_TIME     20

// ---------------- FUNCTION DECLARATIONS ----------------
void initLight(TrafficLight t);
void setLight(TrafficLight t, bool r, bool y, bool g);
void countdown(int seconds);
void runTrafficCycle();

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);

  initLight(road1);
  initLight(road2);

  display.setBrightness(7);

  Serial.println(F("Smart Traffic System Initialized"));
}

// ---------------- LOOP ----------------
void loop() {
  runTrafficCycle();
}

// ---------------- CORE LOGIC ----------------

void runTrafficCycle() {

  // 🚦 ROAD 1 GREEN
  setLight(road1, LOW, LOW, HIGH);
  setLight(road2, HIGH, LOW, LOW);
  countdown(GREEN_TIME);

  // 🟡 ROAD 1 YELLOW
  setLight(road1, LOW, HIGH, LOW);
  countdown(YELLOW_TIME);

  // 🚦 ROAD 2 GREEN
  setLight(road1, HIGH, LOW, LOW);
  setLight(road2, LOW, LOW, HIGH);
  countdown(RED_TIME);

  // 🟡 ROAD 2 YELLOW
  setLight(road2, LOW, HIGH, LOW);
  countdown(YELLOW_TIME);
}

// ---------------- HELPER FUNCTIONS ----------------

// Initialize pins
void initLight(TrafficLight t) {
  pinMode(t.red, OUTPUT);
  pinMode(t.yellow, OUTPUT);
  pinMode(t.green, OUTPUT);
}

// Set light states
void setLight(TrafficLight t, bool r, bool y, bool g) {
  digitalWrite(t.red, r);
  digitalWrite(t.yellow, y);
  digitalWrite(t.green, g);
}

// Display countdown
void countdown(int seconds) {

  uint8_t data[4];

  for (int i = seconds; i >= 0; i--) {

    int tens = i / 10;
    int ones = i % 10;

    data[0] = 0x00;
    data[1] = 0x00;
    data[2] = display.encodeDigit(tens);
    data[3] = display.encodeDigit(ones);

    display.setSegments(data);

    Serial.print(F("Time Left: "));
    Serial.println(i);

    delay(1000);
  }
}
