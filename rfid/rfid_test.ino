/*
  🚀 RFID Module (RC522) - UID Detection & Validation System

  Features:
  - UID reading and formatting
  - Authorized card checking
  - Clean serial output
  - Expandable for real applications

  Author: Venkateswarlu Reddy
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D2
#define RST_PIN D1

MFRC522 rfid(SS_PIN, RST_PIN);

// 🔐 Add your authorized card UID here
String authorizedUID = "YOUR CARD UID";

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  Serial.println(F("\n===================================="));
  Serial.println(F(" RFID RC522 TEST MODULE "));
  Serial.println(F("===================================="));
  Serial.println(F("Scan your RFID card...\n"));
}

void loop() {

  // Check if card is present
  if (!rfid.PICC_IsNewCardPresent()) return;

  // Read card
  if (!rfid.PICC_ReadCardSerial()) return;

  String uid = getUID();

  Serial.print(F("Card UID: "));
  Serial.println(uid);

  // 🔍 Check authorization
  if (uid == authorizedUID) {
    Serial.println(F("✅ Access Granted"));
  } else {
    Serial.println(F("❌ Access Denied"));
  }

  Serial.println(F("---------------------------"));

  rfid.PICC_HaltA();
}

// 🔧 Function to convert UID to readable format
String getUID() {
  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(rfid.uid.uidByte[i], HEX);
    if (i != rfid.uid.size - 1) uid += " ";
  }

  uid.toUpperCase();
  return uid;
}
