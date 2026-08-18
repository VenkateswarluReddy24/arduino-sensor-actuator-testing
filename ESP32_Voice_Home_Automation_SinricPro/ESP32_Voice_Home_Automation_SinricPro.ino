#include <Arduino.h>
#include <WiFi.h>

#include "SinricPro.h"
#include "SinricProSwitch.h"

// ============================================================
// ESP32 VOICE HOME AUTOMATION
// SinricPro + Google Home + Single LED
// ============================================================

#define LED_PIN 2
#define BAUD_RATE 115200

// ------------------------------------------------------------
// WIFI CONFIGURATION
// ------------------------------------------------------------
// Replace these placeholders with your local Wi-Fi details.
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"

// ------------------------------------------------------------
// SINRICPRO CONFIGURATION
// ------------------------------------------------------------
// Never publish real credentials to GitHub.
#define APP_KEY    "YOUR_APP_KEY"
#define APP_SECRET "YOUR_APP_SECRET"
#define SWITCH_ID  "YOUR_DEVICE_ID"

bool ledState = false;

// ============================================================
// LED CONTROL
// ============================================================
void setLED(bool state) {
  ledState = state;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);

  Serial.print("LED STATE: ");
  Serial.println(ledState ? "ON" : "OFF");
}

// ============================================================
// SINRICPRO POWER CALLBACK
// ============================================================
bool onPowerState(const String &deviceId, bool &state) {
  Serial.println();
  Serial.println("--------------------------------");
  Serial.print("Device ID: ");
  Serial.println(deviceId);
  Serial.print("Received command: ");
  Serial.println(state ? "TURN ON" : "TURN OFF");

  setLED(state);

  Serial.print("Recognized action: LED ");
  Serial.println(state ? "ON" : "OFF");
  Serial.print("Free heap: ");
  Serial.println(ESP.getFreeHeap());
  Serial.println("--------------------------------");

  return true;
}

// ============================================================
// WIFI SETUP
// ============================================================
void setupWiFi() {
  Serial.println();
  Serial.println("================================");
  Serial.println("WIFI CONNECTION");
  Serial.println("================================");

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Connecting to Wi-Fi");

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 20000) {
    Serial.print(".");
    delay(250);
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("ERROR: Wi-Fi connection failed.");
    Serial.println("Check WIFI_SSID and WIFI_PASS.");
  }
}

// ============================================================
// SINRICPRO SETUP
// ============================================================
void setupSinricPro() {
  Serial.println();
  Serial.println("================================");
  Serial.println("SINRICPRO SETUP");
  Serial.println("================================");

  SinricProSwitch &mySwitch = SinricPro[SWITCH_ID];

  mySwitch.onPowerState(onPowerState);

  SinricPro.onConnected([]() {
    Serial.println();
    Serial.println("Connected to SinricPro.");
    Serial.println("Cloud connection: ONLINE");

    SinricProSwitch &mySwitch = SinricPro[SWITCH_ID];
    mySwitch.sendPowerStateEvent(ledState);
  });

  SinricPro.onDisconnected([]() {
    Serial.println();
    Serial.println("Disconnected from SinricPro.");
    Serial.println("Cloud connection: OFFLINE");
  });

  SinricPro.begin(APP_KEY, APP_SECRET);

  Serial.println("SinricPro client started.");
}

// ============================================================
// SETUP
// ============================================================
void setup() {
  Serial.begin(BAUD_RATE);
  delay(500);

  Serial.println();
  Serial.println();
  Serial.println("========================================");
  Serial.println("      ESP32 VOICE HOME AUTOMATION");
  Serial.println("========================================");

  pinMode(LED_PIN, OUTPUT);
  setLED(false);

  Serial.println("Hardware initialized.");
  Serial.println("GPIO 2 LED = OFF");

  setupWiFi();

  if (WiFi.status() == WL_CONNECTED) {
    setupSinricPro();
  } else {
    Serial.println();
    Serial.println("SinricPro was not started because Wi-Fi is unavailable.");
  }

  Serial.println();
  Serial.println("========================================");
  Serial.println("SYSTEM STATUS");
  Serial.println("========================================");
  Serial.print("LED: ");
  Serial.println(ledState ? "ON" : "OFF");
  Serial.print("Wi-Fi: ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "CONNECTED" : "DISCONNECTED");
  Serial.print("Free heap: ");
  Serial.println(ESP.getFreeHeap());
  Serial.println("========================================");
}

// ============================================================
// LOOP
// ============================================================
void loop() {
  SinricPro.handle();

  static unsigned long lastWiFiCheck = 0;

  if (millis() - lastWiFiCheck >= 10000) {
    lastWiFiCheck = millis();

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Wi-Fi connection lost. Reconnecting...");
      WiFi.reconnect();
    }
  }
}
