/*
  🚀 Ultrasonic Sensor (HC-SR04) - Precision Measurement Module

  Features:
  - Averaged readings for noise reduction
  - Timeout protection
  - Configurable sample size
  - Clean and reusable function design

  Author: Venkateswarlu Reddy
*/

#define TRIG_PIN 6
#define ECHO_PIN 7

#define MAX_DISTANCE 400.0   // cm
#define MIN_DISTANCE 2.0     // cm
#define SAMPLES 5            // Number of readings for averaging
#define TIMEOUT_US 25000     // 25ms timeout (~4m max range)

float readDistanceCM();

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println(F("\n===================================="));
  Serial.println(F(" HC-SR04 PRECISION TEST MODULE "));
  Serial.println(F("===================================="));
  Serial.println(F("Initializing sensor...\n"));

  delay(1500);
}

void loop() {
  float distance = readDistanceCM();

  if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE) {
    Serial.print(F("Distance: "));
    Serial.print(distance, 2);
    Serial.println(F(" cm"));
  } else {
    Serial.println(F("⚠️ Invalid / Out of Range"));
  }

  delay(400);
}

// 📏 Reads distance with averaging and validation
float readDistanceCM() {
  float total = 0;
  int validSamples = 0;

  for (int i = 0; i < SAMPLES; i++) {

    // Trigger pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, TIMEOUT_US);

    // If no signal received, skip this sample
    if (duration == 0) continue;

    float distance = duration * 0.0343 / 2.0;

    // Validate reading
    if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE) {
      total += distance;
      validSamples++;
    }

    delay(10);
  }

  // If no valid samples, return -1
  if (validSamples == 0) return -1;

  return total / validSamples;
}
