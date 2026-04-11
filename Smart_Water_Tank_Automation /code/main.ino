/*
  💧 Smart Water Tank Automation System (IoT + Safety Engine)

  Features:
  - Automatic pump control using ultrasonic sensor
  - Overflow protection
  - Dry-run detection
  - Manual + Auto mode (Blynk)
  - LCD + LED status system
  - Industrial safety logic

  Author: Venkateswarlu Reddy
*/

// ---------------- CONFIG ----------------
// ⚠️ Create config.h (DO NOT UPLOAD)

/*
#define BLYNK_TEMPLATE_ID "YOUR_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_TOKEN"

const char* WIFI_SSID = "YOUR_WIFI";
const char* WIFI_PASS = "YOUR_PASS";
*/

#include "config.h"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------- PINS ----------------
#define TRIG_PIN D5
#define ECHO_PIN D6
#define RELAY_PIN D7

#define LED_YELLOW D0
#define LED_GREEN  D3
#define LED_RED    D4
#define LED_BLUE   D8

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- THRESHOLDS ----------------
float pumpOnDist     = 10.0;
float pumpOffDist    = 5.0;
float overflowCutoff = 2.5;

// ---------------- SAFETY ----------------
#define MIN_RUN_TIME   15000
#define RESTART_DELAY  20000
#define DRY_RUN_TIME   30000

// ---------------- STATE ----------------
bool autoMode = true;
bool pumpState = false;

float lastDistance = 0;
float prevDistance = 0;

unsigned long pumpStart = 0;
unsigned long pumpStop  = 0;
unsigned long dryTimer  = 0;

bool dryFault = false;
bool overflowFault = false;

BlynkTimer timer;

// ================= BLYNK =================
BLYNK_WRITE(V6)
{
  if(!autoMode)
  {
    pumpState = param.asInt();
    digitalWrite(RELAY_PIN, pumpState ? LOW : HIGH);
  }
}

BLYNK_WRITE(V7)
{
  autoMode = param.asInt();

  if(autoMode)
    Blynk.virtualWrite(V6, 0);
  else
  {
    pumpState = false;
    digitalWrite(RELAY_PIN, HIGH);
  }
}

// ================= DISTANCE =================
float getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000);
  if(duration == 0) return -1;

  return duration * 0.0343 / 2.0;
}

// ================= SAFETY ENGINE =================
void safetyControl(float d)
{
  if(d == -1)
  {
    stopPump();
    return;
  }

  if(d < 2 || d > 35) return;

  lastDistance = d;

  // OVERFLOW
  if(d <= overflowCutoff)
  {
    overflowFault = true;
    stopPump();
    return;
  }
  else overflowFault = false;

  // AUTO MODE
  if(autoMode)
  {
    if(!pumpState && millis() - pumpStop < RESTART_DELAY)
      return;

    if(d > pumpOnDist && !pumpState)
    {
      startPump();
      prevDistance = d;
      dryFault = false;
    }

    if(d < pumpOffDist && pumpState &&
       millis() - pumpStart > MIN_RUN_TIME)
    {
      stopPump();
    }
  }

  // DRY RUN
  if(pumpState && millis() - dryTimer > DRY_RUN_TIME)
  {
    if(abs(d - prevDistance) < 0.8)
    {
      dryFault = true;
      stopPump();
    }

    prevDistance = d;
    dryTimer = millis();
  }
}

// ================= PUMP CONTROL =================
void startPump()
{
  pumpState = true;
  pumpStart = millis();
  dryTimer = millis();
  digitalWrite(RELAY_PIN, LOW);
}

void stopPump()
{
  pumpState = false;
  pumpStop = millis();
  digitalWrite(RELAY_PIN, HIGH);
}

// ================= LED =================
void updateLEDs()
{
  digitalWrite(LED_BLUE, autoMode);
  digitalWrite(LED_YELLOW, !autoMode);
  digitalWrite(LED_RED, pumpState);
  digitalWrite(LED_GREEN, lastDistance < pumpOffDist);
}

// ================= SYSTEM UPDATE =================
void updateSystem()
{
  float d = getDistance();

  safetyControl(d);
  updateLEDs();

  Blynk.virtualWrite(V8, lastDistance);

  lcd.setCursor(0,0);
  lcd.print("Dist:");
  lcd.print(lastDistance,1);
  lcd.print("cm   ");

  lcd.setCursor(0,1);

  if(overflowFault)
    lcd.print("OVERFLOW STOP ");
  else if(dryFault)
    lcd.print("DRY RUN STOP  ");
  else if(autoMode)
    lcd.print(pumpState ? "AUTO RUNNING  " : "AUTO STOPPED  ");
  else
    lcd.print(pumpState ? "MANUAL RUN    " : "MANUAL STOP   ");
}

// ================= SETUP =================
void setup()
{
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);

  lcd.init();
  lcd.backlight();

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  timer.setInterval(2000L, updateSystem);
}

// ================= LOOP =================
void loop()
{
  Blynk.run();
  timer.run();
}
