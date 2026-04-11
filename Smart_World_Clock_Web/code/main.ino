#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>
#include "config.h"

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- SERVER ----------------
ESP8266WebServer server(80);

// ---------------- TIME ----------------
const char* ntpServer = "pool.ntp.org";
long gmtOffset_sec = 19800;
int daylightOffset_sec = 0;

String cityName = "INDIA";

const char* weekDays[] = {
  "SUN","MON","TUE","WED","THU","FRI","SAT"
};

// ---------------- TIMERS ----------------
unsigned long lastUpdate = 0;
#define LCD_INTERVAL 1000

// ================= WEB PAGE =================
String webpage = R"====(
<!DOCTYPE html>
<html>
<head>
<title>World Clock</title>
<style>
body { font-family: Arial; text-align:center; background:#111; color:white; }
button { padding:15px; margin:10px; font-size:20px; width:220px; }
</style>
</head>
<body>
<h1>🌍 WORLD CLOCK</h1>
<button onclick="location.href='/set?city=INDIA&offset=19800'">INDIA</button><br>
<button onclick="location.href='/set?city=LONDON&offset=0'">LONDON</button><br>
<button onclick="location.href='/set?city=NEWYORK&offset=-18000'">NEW YORK</button><br>
<button onclick="location.href='/set?city=TOKYO&offset=32400'">TOKYO</button><br>
<button onclick="location.href='/set?city=SYDNEY&offset=36000'">SYDNEY</button><br>
<button onclick="location.href='/set?city=DUBAI&offset=14400'">DUBAI</button><br>
<button onclick="location.href='/set?city=MOSCOW&offset=10800'">MOSCOW</button><br>
<button onclick="location.href='/set?city=BEIJING&offset=28800'">BEIJING</button>
</body>
</html>
)====";

// ================= SET CITY =================
void setCity(String city, long offset)
{
  cityName = city;
  gmtOffset_sec = offset;

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.println("City Changed: " + cityName);

  lcd.clear();
  lcd.print("City: " + cityName);
  delay(1000);
}

// ================= ROUTES =================
void handleRoot()
{
  server.send(200, "text/html", webpage);
}

void handleSetCity()
{
  if(server.hasArg("city") && server.hasArg("offset"))
  {
    String city = server.arg("city");
    long offset = server.arg("offset").toInt();

    setCity(city, offset);
  }

  handleRoot();
}

// ================= WIFI =================
void connectWiFi()
{
  lcd.print("Connecting WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.print("WiFi Connected");

  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());
}

// ================= DISPLAY =================
void updateDisplay()
{
  time_t now = time(nullptr);
  struct tm* t = localtime(&now);

  char line1[17];
  snprintf(line1, sizeof(line1), "%s %02d/%02d/%04d",
           weekDays[t->tm_wday],
           t->tm_mday,
           t->tm_mon + 1,
           t->tm_year + 1900);

  char line2[17];
  snprintf(line2, sizeof(line2), "%s %02d:%02d:%02d",
           cityName.c_str(),
           t->tm_hour,
           t->tm_min,
           t->tm_sec);

  lcd.setCursor(0,0);
  lcd.print(line1);

  lcd.setCursor(0,1);
  lcd.print(line2);
}

// ================= SETUP =================
void setup()
{
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  connectWiFi();

  // Routes
  server.on("/", handleRoot);
  server.on("/set", handleSetCity);

  server.begin();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

// ================= LOOP =================
void loop()
{
  server.handleClient();

  if(millis() - lastUpdate > LCD_INTERVAL)
  {
    lastUpdate = millis();
    updateDisplay();
  }
}
