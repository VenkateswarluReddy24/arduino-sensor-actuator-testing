/*
  🚀 TTP Touch Sensor Module (Professional Input Handler)

  Features:
  - Stable touch detection (debounced)
  - State change detection (PRESS / RELEASE)
  - Reusable input module design
  - Serial debug output

  Author: Venkateswarlu Reddy
*/

#define TOUCH_PIN 2

#define DEBOUNCE_DELAY 50  // ms

bool lastStableState = LOW;
bool lastReading = LOW;
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TOUCH_PIN, INPUT);

  Serial.println(F("\n=============================="));
  Serial.println(F(" TTP TOUCH SENSOR MODULE "));
  Serial.println(F("=============================="));
  Serial.println(F("Touch the sensor...\n"));
}

void loop() {
  bool reading = digitalRead(TOUCH_PIN);

  // If state changed, reset debounce timer
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  // If stable for debounce time
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {

    if (reading != lastStableState) {
      lastStableState = reading;

      if (lastStableState == HIGH) {
        onTouchPressed();
      } else {
        onTouchReleased();
      }
    }
  }

  lastReading = reading;
}

// 🔘 Touch Press Event
void onTouchPressed() {
  Serial.println(F("👉 Touch Detected"));
}

// 🔘 Touch Release Event
void onTouchReleased() {
  Serial.println(F("👈 Touch Released"));
}
