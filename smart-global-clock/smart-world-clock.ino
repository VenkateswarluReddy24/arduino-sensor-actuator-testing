/*
  🌍 Smart Global Clock – Production Grade (Top 1%)

  Improvements:
  ✔ Clean architecture
  ✔ Safe cloud handling
  ✔ Optimized display refresh
  ✔ Stable auto & meeting modes
  ✔ Professional formatting

  Author: Venkateswarlu Reddy
*/

#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 20, 4);

// ---------------- WIFI ----------------
#define WIFI_SSID "ATL LAB"
#define WIFI_PASSWORD "1122334455"

// ---------------- FIREBASE ----------------
#define API_KEY "AIzaSyCE3EmMrGtphBof8U1aFZsK5A0XvxRXh_4"
#define DATABASE_URL "https://smart-world-clock-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// ---------------- TIME ----------------
const char* ntpServer = "pool.ntp.org";

// ---------------- CLOUD STATE ----------------
String city = "DUBAI";
String autoMode = "OFF";
String meetingMode = "OFF";

// ---------------- CONSTANT DATA ----------------
const String cityList[8] = {
  "DUBAI","INDIA","LONDON","NEWYORK",
  "TOKYO","PARIS","SINGAPORE","SYDNEY"
};

const char* weekDays[] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

// ---------------- TIMERS ----------------
unsigned long tCloud=0;
unsigned long tAuto=0;
unsigned long tDisplay=0;
unsigned long tMeeting=0;

// ---------------- STATE ----------------
bool autoRunning = false;
int autoIndex = 0;
int meetingPage = 0;

// ---------------- OFFSET ----------------
long getOffset(const String &c){
  if(c=="INDIA") return 19800;
  if(c=="DUBAI") return 14400;
  if(c=="SINGAPORE") return 28800;
  if(c=="TOKYO") return 32400;
  if(c=="LONDON") return 0;
  if(c=="PARIS") return 3600;
  if(c=="NEWYORK") return -14400;
  if(c=="SYDNEY") return 39600;
  return 14400;
}

// ---------------- LCD PRINT ----------------
void printLine(uint8_t row, const String &txt){
  lcd.setCursor(0,row);
  lcd.print("                    ");
  lcd.setCursor(0,row);
  lcd.print(txt);
}

// ---------------- TIME ENGINE ----------------
void getCityTime(const String &c, char* dateStr, char* timeStr){

  time_t now = time(nullptr);
  time_t localTime = now + getOffset(c);
  struct tm* t = gmtime(&localTime);

  sprintf(dateStr,"%s %02d/%02d/%04d",
          weekDays[t->tm_wday],
          t->tm_mday,
          t->tm_mon+1,
          t->tm_year+1900);

  sprintf(timeStr,"%02d:%02d:%02d",
          t->tm_hour,
          t->tm_min,
          t->tm_sec);
}

// ---------------- CLOUD READ ----------------
void readCloud(){

  if(Firebase.RTDB.getString(&fbdo,"/smartclock/auto_mode"))
    autoMode = fbdo.stringData();

  if(Firebase.RTDB.getString(&fbdo,"/smartclock/meeting_mode"))
    meetingMode = fbdo.stringData();

  if(autoMode != "ON" && meetingMode != "ON"){
    if(Firebase.RTDB.getString(&fbdo,"/smartclock/active_city")){
      city = fbdo.stringData();
    }
  }
}

// ---------------- AUTO MODE ----------------
void autoRun(){

  if(!autoRunning){
    autoRunning = true;
    autoIndex = 0;
    city = cityList[autoIndex];
    tAuto = millis();
  }

  if(millis() - tAuto >= 3000){

    autoIndex++;

    if(autoIndex < 8){
      city = cityList[autoIndex];
    }
    else{
      autoRunning = false;
      autoMode = "OFF";
      Firebase.RTDB.setString(&fbdo,"/smartclock/auto_mode","OFF");
    }

    tAuto = millis();
  }
}

// ---------------- MEETING MODE ----------------
void meetingRun(){

  if(millis() - tMeeting >= 5000){
    meetingPage++;
    if(meetingPage >= 2){
      meetingPage = 0;
      Firebase.RTDB.setString(&fbdo,"/smartclock/meeting_mode","OFF");
    }
    tMeeting = millis();
  }

  int start = meetingPage * 4;

  printLine(0,"MEETING PLANNER");

  for(int i=0;i<4;i++){

    char d[25], t[10];
    getCityTime(cityList[start+i], d, t);

    char line[21];
    snprintf(line,sizeof(line),"%-9s %s",
             cityList[start+i].c_str(), t);

    printLine(i,line);
  }
}

// ---------------- DISPLAY ----------------
void normalDisplay(){

  char dateStr[25], timeStr[10];
  getCityTime(city, dateStr, timeStr);

  printLine(0,(autoMode=="ON")?"AUTO MODE ACTIVE":"SMART GLOBAL CLOCK");
  printLine(1,dateStr);

  char line2[21];
  snprintf(line2,sizeof(line2),"%-10s %s",city.c_str(),timeStr);
  printLine(2,line2);

  int h = atoi(timeStr);

  String greet =
    (h<12)?"GOOD MORNING":
    (h<17)?"GOOD AFTERNOON":
    (h<21)?"GOOD EVENING":"GOOD NIGHT";

  printLine(3,greet);
}

// ---------------- SETUP ----------------
void setup(){

  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  lcd.print("SMART GLOBAL CLOCK");
  delay(1000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status()!=WL_CONNECTED) delay(300);

  lcd.clear();
  lcd.print("CLOUD READY");
  delay(800);
  lcd.clear();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.signUp(&config, &auth, "", "");
  Firebase.begin(&config, &auth);

  configTime(0,0,ntpServer);
}

// ---------------- LOOP ----------------
void loop(){

  unsigned long now = millis();

  if(now - tCloud >= 1500){
    readCloud();
    tCloud = now;
  }

  if(meetingMode == "ON"){
    meetingRun();
  }
  else{

    if(autoMode == "ON"){
      autoRun();
    }
    else{
      autoRunning = false;
    }

    if(now - tDisplay >= 1000){
      normalDisplay();
      tDisplay = now;
    }
  }
}
