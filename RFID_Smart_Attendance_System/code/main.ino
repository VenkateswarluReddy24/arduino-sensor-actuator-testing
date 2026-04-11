/*
  📡 RFID-Based Smart Attendance System (ESP8266 + Google Sheets)

  Features:
  - RFID UID detection
  - Student identification system
  - WiFi-based cloud logging
  - Google Sheets integration
  - Secure credential handling

  Author: Venkateswarlu Reddy
*/

// ---------------- CONFIG ----------------
// ⚠️ Create config.h and DO NOT upload to GitHub



#include "config.h"

#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// ---------------- RFID ----------------
#define SS_PIN  D4
#define RST_PIN D3

MFRC522 rfid(SS_PIN, RST_PIN);

// ---------------- NETWORK ----------------
WiFiClientSecure client;

// ---------------- VARIABLES ----------------
String studentName = "";
String studentSection = "";

unsigned long lastScanTime = 0;
const int SCAN_DELAY = 5000;

// ------------------------------------------------
// UID CONVERSION
// ------------------------------------------------
String getUID()
{
  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++)
  {
    if (rfid.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  uid.toUpperCase();
  return uid;
}

// ------------------------------------------------
// STUDENT DATABASE
// ------------------------------------------------
void identifyStudent(String uid)
{
  if (uid == "64BFFB03") {
    studentName = "Priya";
    studentSection = "A";
  }
  else if (uid == "4677FE03") {
    studentName = "Rahul";
    studentSection = "B";
  }
  else if (uid == "5EF7FB03") {
    studentName = "Kiran";
    studentSection = "C";
  }
  else {
    studentName = "Unknown";
    studentSection = "-";
  }
}

// ------------------------------------------------
// SEND DATA TO GOOGLE SHEET
// ------------------------------------------------
void sendToSheet(String uid)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("[ERROR] WiFi not connected");
    return;
  }

  String url = String(WEB_APP_URL) +
               "?name=" + studentName +
               "&uid=" + uid +
               "&section=" + studentSection;

  Serial.println("[HTTP] Sending Data...");
  Serial.println(url);

  client.setInsecure();

  HTTPClient http;

  if (http.begin(client, url))
  {
    int httpCode = http.GET();

    Serial.print("[HTTP] Code: ");
    Serial.println(httpCode);

    if (httpCode > 0)
    {
      Serial.println("[SERVER] " + http.getString());
    }
    else
    {
      Serial.println("[ERROR] Request failed");
    }

    http.end();
  }
}

// ------------------------------------------------
// WIFI CONNECT
// ------------------------------------------------
void connectWiFi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ------------------------------------------------
// SETUP
// ------------------------------------------------
void setup()
{
  Serial.begin(115200);

  SPI.begin();
  rfid.PCD_Init();

  Serial.println("RFID Attendance System Started");

  connectWiFi();
}

// ------------------------------------------------
// LOOP
// ------------------------------------------------
void loop()
{
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  if (millis() - lastScanTime < SCAN_DELAY) return;

  lastScanTime = millis();

  String uid = getUID();

  Serial.print("UID: ");
  Serial.println(uid);

  identifyStudent(uid);

  if (studentName != "Unknown")
  {
    sendToSheet(uid);
    Serial.println("[SUCCESS] Attendance Logged");
  }
  else
  {
    Serial.println("[WARNING] Unknown Card");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
