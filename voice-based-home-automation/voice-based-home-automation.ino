#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

#define WIFI_SSID "YOUR_WIFI"
#define WIFI_PASS "YOUR_PASSWORD"

#define APP_KEY "YOUR_APP_KEY"
#define APP_SECRET "YOUR_APP_SECRET"

#define DEVICE_ID "YOUR_DEVICE_ID"

#define RELAY_PIN D1

bool onPowerState(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN, state ? LOW : HIGH);
  Serial.println(state ? "ON" : "OFF");
  return true;
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");

  SinricProSwitch &mySwitch = SinricPro[DEVICE_ID];
  mySwitch.onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  SinricPro.handle();
}
