#include "config.h"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// ---------------- RELAY ----------------
#define RELAY_PIN D5
#define VPIN_RELAY V2

bool relayState = false;

// ---------------- FUNCTION ----------------
void updateRelay(bool state)
{
  relayState = state;

  // Active LOW relay support
  digitalWrite(RELAY_PIN, state ? LOW : HIGH);

  Serial.print("[RELAY] ");
  Serial.println(state ? "ON" : "OFF");
}

// ---------------- SETUP ----------------
void setup()
{
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // OFF

  Serial.println("Smart Irrigation System Starting...");

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
}

// ---------------- LOOP ----------------
void loop()
{
  Blynk.run();
}

// ---------------- BLYNK HANDLER ----------------
BLYNK_WRITE(VPIN_RELAY)
{
  int value = param.asInt();
  updateRelay(value);
}
