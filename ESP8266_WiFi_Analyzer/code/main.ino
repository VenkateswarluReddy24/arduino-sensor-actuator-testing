#include <ESP8266WiFi.h>

// ---------------- PARAMETERS ----------------
#define SCAN_INTERVAL 10000   // 10 seconds

unsigned long lastScanTime = 0;

// ================= ENCRYPTION TYPE =================
String getEncryptionType(uint8_t encType)
{
  switch (encType)
  {
    case ENC_TYPE_WEP:  return "WEP";
    case ENC_TYPE_TKIP: return "WPA";
    case ENC_TYPE_CCMP: return "WPA2";
    case ENC_TYPE_AUTO: return "AUTO";
    case ENC_TYPE_NONE: return "OPEN";
    default: return "UNKNOWN";
  }
}

// ================= SIGNAL QUALITY =================
String getSignalQuality(int rssi)
{
  if (rssi >= -50) return "Excellent";
  else if (rssi >= -60) return "Good";
  else if (rssi >= -70) return "Fair";
  else return "Weak";
}

// ================= SCAN FUNCTION =================
void scanWiFi()
{
  Serial.println("\n🔍 Scanning WiFi Networks...");

  int n = WiFi.scanNetworks();

  if (n == 0)
  {
    Serial.println("❌ No networks found");
    return;
  }

  Serial.printf("✅ %d networks found\n\n", n);

  for (int i = 0; i < n; i++)
  {
    Serial.print("📶 SSID: ");
    Serial.print(WiFi.SSID(i));

    Serial.print(" | RSSI: ");
    Serial.print(WiFi.RSSI(i));
    Serial.print(" dBm");

    Serial.print(" | Quality: ");
    Serial.print(getSignalQuality(WiFi.RSSI(i)));

    Serial.print(" | Security: ");
    Serial.print(getEncryptionType(WiFi.encryptionType(i)));

    Serial.print(" | Channel: ");
    Serial.print(WiFi.channel(i));

    Serial.println();
  }
}

// ================= SETUP =================
void setup()
{
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.println("📡 WiFi Analyzer Started");
}

// ================= LOOP =================
void loop()
{
  if (millis() - lastScanTime > SCAN_INTERVAL)
  {
    lastScanTime = millis();
    scanWiFi();
  }
}
