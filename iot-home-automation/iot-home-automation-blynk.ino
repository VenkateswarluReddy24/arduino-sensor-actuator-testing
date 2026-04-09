/*
  🏠 IoT Smart Home Automation System (Blynk + ESP8266)

  Features:
  - Modular relay control system
  - Active LOW relay handling
  - Real-time IoT control via Blynk
  - Serial monitoring for debugging
  - Scalable architecture

  Author: Venkateswarlu Reddy
*/

#define BLYNK_TEMPLATE_ID "template id"
#define BLYNK_TEMPLATE_NAME "Template name"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// ---------------- CREDENTIALS ----------------
char auth[] = "auth token";
char ssid[] = "wifi name";
char pass[] = "wifi password";

// ---------------- RELAY CONFIG ----------------
// Active LOW Relays
#define RELAY1 D1   // Light 1
#define RELAY2 D2   // Light 2
#define RELAY3 D3   // Fan

// ---------------- FUNCTION DECLARATIONS ----------------
void controlRelay(int relayPin, int state, String deviceName);

// ---------------- SETUP ----------------
void setup()
{
  Serial.begin(9600);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);

  // Ensure all devices OFF at startup
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);

  Serial.println("Initializing Smart Home System...");

  Blynk.begin(auth, ssid, pass);

  Serial.println("System Ready");
}

// ---------------- LOOP ----------------
void loop()
{
  Blynk.run();
}

// ---------------- RELAY CONTROL FUNCTION ----------------
void controlRelay(int relayPin, int state, String deviceName)
{
  if(state == 1)
  {
    digitalWrite(relayPin, LOW);  // ON
    Serial.println(deviceName + " ON");
  }
  else
  {
    digitalWrite(relayPin, HIGH); // OFF
    Serial.println(deviceName + " OFF");
  }
}

// ---------------- BLYNK CONTROLS ----------------

// Light 1
BLYNK_WRITE(V6)
{
  int state = param.asInt();
  controlRelay(RELAY1, state, "Light 1");
}

// Light 2
BLYNK_WRITE(V7)
{
  int state = param.asInt();
  controlRelay(RELAY2, state, "Light 2");
}

// Fan
BLYNK_WRITE(V8)
{
  int state = param.asInt();
  controlRelay(RELAY3, state, "Fan");
}
