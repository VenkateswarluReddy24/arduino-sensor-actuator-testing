/*
  🌡️ IoT Temperature & Humidity Monitor (Blynk + ESP8266)

  Features:
  - Real-time temperature & humidity monitoring
  - Secure credential handling
  - Non-blocking sensor updates
  - Serial + cloud logging
  - Stable IoT communication

  Author: Venkateswarlu Reddy
*/

// ---------------- CONFIG FILE ----------------
// ⚠️ Create a separate file named "config.h" and store secrets there

/*
  config.h content:

  #define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
  #define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
  #define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

  const char* WIFI_SSID = "YOUR_WIFI";
  const char* WIFI_PASS = "YOUR_PASSWORD";
*/

#include "config.h"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// ---------------- DHT CONFIG ----------------
#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// ---------------- FUNCTION ----------------
void sendSensorData() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // -------- VALIDATION --------
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("[ERROR] DHT Read Failed");
    return;
  }

  // -------- SERIAL DEBUG --------
  Serial.print("[DATA] Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // -------- SEND TO BLYNK --------
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
}

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(9600);
  dht.begin();

  Serial.println("IoT Sensor Initializing...");

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  // Read every 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

// ---------------- LOOP ----------------
void loop() {

  Blynk.run();
  timer.run();
}
