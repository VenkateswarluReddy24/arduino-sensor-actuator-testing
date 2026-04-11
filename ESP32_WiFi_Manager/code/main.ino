#include <WiFi.h>
#include "config.h"

// ---------------- PARAMETERS ----------------
#define WIFI_TIMEOUT 15000   // 15 seconds
#define RETRY_DELAY  5000    // Retry delay

unsigned long connectStart = 0;
bool isConnected = false;

// ================= CONNECT FUNCTION =================
void connectWiFi()
{
  Serial.println("\n🔌 Connecting to WiFi...");

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  connectStart = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - connectStart < WIFI_TIMEOUT)
  {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    isConnected = true;

    Serial.println("\n✅ WiFi Connected");
    Serial.print("📡 IP Address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("\n❌ Connection Failed (Timeout)");
    isConnected = false;
  }
}

// ================= RECONNECT =================
void maintainWiFi()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("\n⚠ WiFi Disconnected. Reconnecting...");
    delay(RETRY_DELAY);
    connectWiFi();
  }
}

// ================= SETUP =================
void setup()
{
  Serial.begin(115200);
  delay(1000);

  connectWiFi();
}

// ================= LOOP =================
void loop()
{
  maintainWiFi();

  // Example task
  if (isConnected)
  {
    Serial.println("📶 WiFi Stable...");
  }

  delay(3000);
}
