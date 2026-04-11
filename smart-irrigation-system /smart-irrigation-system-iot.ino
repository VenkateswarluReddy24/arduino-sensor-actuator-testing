/*
  🌱 IoT Smart Irrigation System (Industry-Level)

  Features:
  - Auto & Manual mode control
  - Soil moisture monitoring (percentage + raw)
  - Non-blocking timing (millis)
  - Relay protection logic
  - Scalable modular design

  Author: Venkateswarlu Reddy
*/

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "YOUR TEMPLATE ID"
#define BLYNK_TEMPLATE_NAME "YOUR TEMPLATE NAME"
#define BLYNK_AUTH_TOKEN "YOUR AUTH TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// ---------------- WIFI ----------------
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR WIFI NAME";
char pass[] = "YOUR WIFI PASSWORD";

// ---------------- HARDWARE ----------------
#define SOIL_PIN A0
#define RELAY_PIN D1   // Active LOW relay

// ---------------- CONFIG ----------------
#define DRY_THRESHOLD 30        // % below → pump ON
#define SAMPLE_INTERVAL 1000    // ms

// ---------------- VARIABLES ----------------
int soilValue = 0;
int soilPercent = 0;

bool manualMode = false;
bool pumpManual = false;

unsigned long previousMillis = 0;

// ---------------- FUNCTION DECLARATIONS ----------------
void readSoilSensor();
void updateBlynk();
void autoControl();
void manualControl();
void setPump(bool state);

// ---------------- BLYNK HANDLERS ----------------

// Mode switch (AUTO / MANUAL)
BLYNK_WRITE(V0)
{
  manualMode = param.asInt();
  Serial.println(manualMode ? "Mode: MANUAL" : "Mode: AUTO");
}

// Manual pump control
BLYNK_WRITE(V1)
{
  pumpManual = param.asInt();
}

// ---------------- SETUP ----------------
void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Pump OFF

  Serial.println("Initializing Smart Irrigation System...");

  Blynk.begin(auth, ssid, pass);

  Serial.println("System Ready");
}

// ---------------- LOOP ----------------
void loop()
{
  Blynk.run();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= SAMPLE_INTERVAL)
  {
    previousMillis = currentMillis;

    readSoilSensor();
    updateBlynk();

    if (!manualMode)
      autoControl();
    else
      manualControl();
  }
}

// ---------------- SENSOR READING ----------------
void readSoilSensor()
{
  long total = 0;

  // Average filtering (reduce noise)
  for(int i = 0; i < 5; i++)
  {
    total += analogRead(SOIL_PIN);
    delay(10);
  }

  soilValue = total / 5;

  // Convert to percentage
  soilPercent = map(soilValue, 1024, 0, 0, 100);

  Serial.print("Soil Raw: ");
  Serial.print(soilValue);
  Serial.print(" | Moisture: ");
  Serial.print(soilPercent);
  Serial.println("%");
}

// ---------------- BLYNK UPDATE ----------------
void updateBlynk()
{
  Blynk.virtualWrite(V4, soilValue);
  Blynk.virtualWrite(V3, soilPercent);
}

// ---------------- AUTO MODE ----------------
void autoControl()
{
  if (soilPercent < DRY_THRESHOLD)
  {
    setPump(true);
  }
  else
  {
    setPump(false);
  }
}

// ---------------- MANUAL MODE ----------------
void manualControl()
{
  setPump(pumpManual);
}

// ---------------- PUMP CONTROL ----------------
void setPump(bool state)
{
  if (state)
  {
    digitalWrite(RELAY_PIN, LOW); // ON
    Serial.println("Pump: ON");
  }
  else
  {
    digitalWrite(RELAY_PIN, HIGH); // OFF
    Serial.println("Pump: OFF");
  }
}
