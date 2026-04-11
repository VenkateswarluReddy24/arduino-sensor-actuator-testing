/*
  🔥 Industrial Fire & Gas Alert System (IoT + SMTP)

  Features:
  - Real-time gas monitoring (MQ2)
  - Adaptive baseline calibration
  - Threshold-based alert system
  - Email notification via SMTP
  - LCD status display
  - Buzzer alert system
  - Alert cooldown protection

  Author: Venkateswarlu Reddy
*/

#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>
#include <LiquidCrystal_I2C.h>

// ---------------- WIFI ----------------
#define WIFI_SSID "YOUR WIFI NAME"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"

// ---------------- SMTP ----------------
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT PORT NUMBER

#define AUTHOR_EMAIL "SENDER EMAIL"
#define AUTHOR_PASSWORD "AUTHOR PASSWORD"
#define RECIPIENT_EMAIL "RECIPIENT EMAIL"

// ---------------- HARDWARE ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define GAS_PIN A0
#define BUZZER_PIN D5

// ---------------- PARAMETERS ----------------
#define SAMPLE_COUNT 50
#define THRESHOLD_OFFSET 200
#define ALERT_COOLDOWN 30000   // 30 seconds

// ---------------- VARIABLES ----------------
int baseline = 0;
unsigned long lastAlertTime = 0;

SMTPSession smtp;

// ---------------- FUNCTION DECLARATIONS ----------------
void connectWiFi();
void calibrateSensor();
int readGasFiltered();
void triggerAlert(int gasValue);
void sendEmail(int gasValue);

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(115200);
  delay(1000);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.init();
  lcd.backlight();

  lcd.print("Factory Safety");
  delay(2000);

  connectWiFi();
  calibrateSensor();

  lcd.clear();
  lcd.print("Monitoring...");
}

// ---------------- LOOP ----------------
void loop() {

  int gasValue = readGasFiltered();
  int threshold = baseline + THRESHOLD_OFFSET;

  Serial.print("Gas: ");
  Serial.println(gasValue);

  lcd.setCursor(0,0);
  lcd.print("Gas:");
  lcd.print(gasValue);
  lcd.print("   ");

  if (gasValue > threshold) {

    lcd.setCursor(0,1);
    lcd.print("ALERT!        ");

    if (millis() - lastAlertTime > ALERT_COOLDOWN) {
      triggerAlert(gasValue);
      lastAlertTime = millis();
    }

  } else {

    lcd.setCursor(0,1);
    lcd.print("Safe          ");
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(1000);
}

// ---------------- WIFI ----------------
void connectWiFi() {

  lcd.clear();
  lcd.print("Connecting WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  lcd.clear();
  lcd.print("WiFi Connected");

  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());

  delay(2000);
}

// ---------------- CALIBRATION ----------------
void calibrateSensor() {

  lcd.clear();
  lcd.print("Calibrating...");
  delay(3000);

  long total = 0;

  for (int i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(GAS_PIN);
    delay(100);
  }

  baseline = total / SAMPLE_COUNT;

  Serial.print("Baseline: ");
  Serial.println(baseline);
}

// ---------------- FILTERED READING ----------------
int readGasFiltered() {

  long total = 0;

  for (int i = 0; i < 5; i++) {
    total += analogRead(GAS_PIN);
    delay(10);
  }

  return total / 5;
}

// ---------------- ALERT ----------------
void triggerAlert(int gasValue) {

  Serial.println("🔥 GAS LEAK DETECTED");

  digitalWrite(BUZZER_PIN, HIGH);
  delay(1500);
  digitalWrite(BUZZER_PIN, LOW);

  sendEmail(gasValue);
}

// ---------------- EMAIL ----------------
void sendEmail(int gasValue) {

  ESP_Mail_Session session;

  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;

  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;

  SMTP_Message message;

  message.sender.name = "Factory Safety System";
  message.sender.email = AUTHOR_EMAIL;

  message.subject = "URGENT: Gas Leakage Detected";

  message.addRecipient("Factory Manager", RECIPIENT_EMAIL);

  String textMsg = "ALERT!\n\n";
  textMsg += "Gas Leakage Detected\n";
  textMsg += "Gas Value: " + String(gasValue) + "\n";
  textMsg += "Baseline: " + String(baseline) + "\n\n";
  textMsg += "Immediate Action Required";

  message.text.content = textMsg;

  if (!smtp.connect(&session)) {
    Serial.println("SMTP Failed");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Email Failed");
  } else {
    Serial.println("Email Sent");
  }

  smtp.closeSession();
}
