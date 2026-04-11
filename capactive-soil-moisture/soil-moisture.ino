/*
  🌱 Capacitive Soil Moisture Sensor – Smart Test Module

  Features:
  - Clean sensor reading
  - Moisture percentage estimation
  - Serial monitor visualization
  - Calibration-ready design

  Author: Venkateswarlu Reddy
*/

#define SOIL_SENSOR A0

// Calibration values (adjust based on your sensor)
#define DRY_VALUE 800
#define WET_VALUE 300

void setup() {
  Serial.begin(9600);
  pinMode(SOIL_SENSOR, INPUT);

  Serial.println("=================================");
  Serial.println("  SOIL MOISTURE SENSOR TEST");
  Serial.println("=================================");
}

void loop() {

  int rawValue = analogRead(SOIL_SENSOR);

  // Convert to percentage
  int moisturePercent = map(rawValue, DRY_VALUE, WET_VALUE, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  // Display clean output
  Serial.print("Raw: ");
  Serial.print(rawValue);

  Serial.print(" | Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  delay(1000);
}
