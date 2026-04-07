/*
  🚀 ULTRASONIC SENSOR – PRECISION TEST CODE (Top 1%)
  Components:
    - Arduino Uno / Nano
    - HC-SR04 Ultrasonic Sensor
  Features:
    ✅ Floating-point distance measurement
    ✅ Noise-free readings using averaging
    ✅ Elegant, aligned Serial output
    ✅ Auto-status message when out of range
*/

#define TRIG_PIN 6
#define ECHO_PIN 7

float getDistanceCM();  // Function prototype

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.println(F("==================================="));
  Serial.println(F("   HC-SR04 ULTRASONIC SENSOR TEST   "));
  Serial.println(F("==================================="));
  Serial.println(F("Place an object in front of sensor..."));
  Serial.println(F("Distance will be shown in centimeters"));
  Serial.println(F("-----------------------------------\n"));
  delay(2000);
}

void loop() {
  float distance = getDistanceCM();
  
  if (distance > 0 && distance < 400) {  // Valid range of HC-SR04
    Serial.print(F("Distance: "));
    Serial.print(distance, 2);  // Show 2 decimal places
    Serial.println(F(" cm"));
  } else {
    Serial.println(F("⚠️  Out of Range"));
  }

  delay(500);
}

// Function to get stable distance reading
float getDistanceCM() {
  float total = 0;
  int samples = 5; // Take 5 samples for stable average

  for (int i = 0; i < samples; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 25000); // Timeout 25ms (~4m max)
    
    // Convert duration to distance (speed of sound = 343 m/s)
    float distance = duration * 0.0343 / 2.0;
    total += distance;
    delay(10);
  }

  return total / samples;  // Average of all samples
}
