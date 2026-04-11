#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <SPI.h>
#include <MFRC522.h>
#include <time.h>

// ---------------- RFID ----------------
#define SS_PIN D2
#define RST_PIN D1
MFRC522 rfid(SS_PIN, RST_PIN);

// ---------------- NETWORK ----------------
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

// ---------------- SYSTEM ----------------
String busID = "Bus-03";

#define TOTAL_STUDENTS 3

String studentUID[TOTAL_STUDENTS] = {
  "73DECD26",
  "339CDB13",
  "935DFD03"
};

String studentName[TOTAL_STUDENTS] = {
  "Parnitha",
  "Varshitha",
  "Manasa"
};

int studentState[TOTAL_STUDENTS] = {0};
unsigned long stateTime[TOTAL_STUDENTS] = {0};

// ---------------- TIMING ----------------
#define RESET_INTERVAL 30000
#define SCAN_GAP 3500

unsigned long lastScanTime = 0;

// ================= WIFI =================
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
}

// ================= TIME =================
void setupTime()
{
  configTime(19800, 0, "pool.ntp.org");

  while (time(nullptr) < 100000)
  {
    delay(500);
  }
}

String getTimeStamp()
{
  time_t now = time(nullptr);
  struct tm* t = localtime(&now);

  char buffer[25];
  strftime(buffer, sizeof(buffer), "%d-%m %H:%M:%S", t);

  return String(buffer);
}

// ================= UID =================
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

// ================= TELEGRAM =================
void sendTelegram(String msg)
{
  bot.sendMessage(CHAT_ID, msg, "");
}

// ================= SETUP =================
void setup()
{
  Serial.begin(115200);

  SPI.begin();
  rfid.PCD_Init();

  client.setInsecure();

  connectWiFi();
  setupTime();

  Serial.println("Smart Transport System Ready");
}

// ================= LOOP =================
void loop()
{
  resetStates();

  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  if (millis() - lastScanTime < SCAN_GAP) return;
  lastScanTime = millis();

  String uid = getUID();

  Serial.print("UID: ");
  Serial.println(uid);

  processCard(uid);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// ================= RESET =================
void resetStates()
{
  for(int i = 0; i < TOTAL_STUDENTS; i++)
  {
    if(studentState[i] > 0 && millis() - stateTime[i] > RESET_INTERVAL)
    {
      studentState[i] = 0;
    }
  }
}

// ================= PROCESS =================
void processCard(String uid)
{
  String timeStamp = getTimeStamp();

  for(int i = 0; i < TOTAL_STUDENTS; i++)
  {
    if(uid == studentUID[i])
    {
      handleStudent(i, timeStamp);
      return;
    }
  }

  sendUnknownAlert(timeStamp);
}

// ================= STUDENT LOGIC =================
void handleStudent(int i, String timeStamp)
{
  String msg;

  if(studentState[i] == 0)
  {
    studentState[i] = 1;
    stateTime[i] = millis();

    msg = "🚌 BUS: " + busID +
          "\n👤 Student: " + studentName[i] +
          "\n📍 Status: Boarded" +
          "\n🕒 Time: " + timeStamp;
  }
  else if(studentState[i] == 1)
  {
    studentState[i] = 2;
    stateTime[i] = millis();

    msg = "🏠 BUS: " + busID +
          "\n👤 Student: " + studentName[i] +
          "\n📍 Status: Returned" +
          "\n🕒 Time: " + timeStamp;
  }
  else
  {
    msg = "⚠ BUS: " + busID +
          "\n👤 Student: " + studentName[i] +
          "\n🚫 Duplicate Scan Blocked" +
          "\n🕒 Time: " + timeStamp;
  }

  sendTelegram(msg);
}

// ================= UNKNOWN =================
void sendUnknownAlert(String timeStamp)
{
  String msg = "🚨 SECURITY ALERT" +
               "\n🚌 BUS: " + busID +
               "\n⚠ Unknown RFID Detected" +
               "\n🕒 Time: " + timeStamp;

  sendTelegram(msg);
}
