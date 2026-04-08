/*
  🚀 WiFi Robot with GPS Tracking (Industry-Level System)

  Features:
  - WiFi robot control via HTTP API
  - Real-time GPS tracking
  - Web dashboard + Google Maps integration
  - Modular architecture (Motor + GPS separation)
  - Safe speed handling

  Author: Venkateswarlu Reddy
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// ---------------- WIFI ----------------
const char* ssid = "YOUR WIFI NAME";
const char* password = "YOUR WIFI PASSWORD";

ESP8266WebServer server(80);

// ---------------- GPS ----------------
TinyGPSPlus gps;
SoftwareSerial gpsSerial(D3, D4);

String latitude = "0";
String longitude = "0";

// ---------------- MOTOR ----------------
#define IN1 D1
#define IN2 D2
#define IN3 D5
#define IN4 D6
#define ENA D7
#define ENB D8

#define MAX_PWM 1023

int speedValue = 800;

// ---------------- FUNCTION DECLARATIONS ----------------
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopRobot();
void setSpeed();
void setMotor(int in1, int in2, bool forward);
void updateGPS();
void handleGPS();
void gpsPage();
void getGPS();

// ---------------- SETUP ----------------
void setup(){

  Serial.begin(115200);
  gpsSerial.begin(9600);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWriteRange(MAX_PWM);
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  WiFi.softAP(ssid, password);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);

  Serial.print("Robot IP: ");
  Serial.println(WiFi.softAPIP());

  // Routes
  server.on("/forward", moveForward);
  server.on("/back", moveBackward);
  server.on("/left", turnLeft);
  server.on("/right", turnRight);
  server.on("/stop", stopRobot);
  server.on("/speed", setSpeed);

  server.on("/gps", getGPS);
  server.on("/", gpsPage);

  server.begin();

  Serial.println("🚀 GPS Robot System Ready");
}

// ---------------- LOOP ----------------
void loop(){
  server.handleClient();
  updateGPS();
}

// ---------------- MOTOR CONTROL ----------------

void setMotor(int in1, int in2, bool forward){
  digitalWrite(in1, forward);
  digitalWrite(in2, !forward);
}

void moveForward(){
  setMotor(IN1, IN2, true);
  setMotor(IN3, IN4, true);
  server.send(200,"text/plain","OK");
}

void moveBackward(){
  setMotor(IN1, IN2, false);
  setMotor(IN3, IN4, false);
  server.send(200,"text/plain","OK");
}

void turnLeft(){
  setMotor(IN1, IN2, false);
  setMotor(IN3, IN4, true);
  server.send(200,"text/plain","OK");
}

void turnRight(){
  setMotor(IN1, IN2, true);
  setMotor(IN3, IN4, false);
  server.send(200,"text/plain","OK");
}

void stopRobot(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  server.send(200,"text/plain","OK");
}

// ---------------- SPEED ----------------

void setSpeed(){
  int sliderValue = server.arg("value").toInt();
  sliderValue = constrain(sliderValue,0,255);

  speedValue = map(sliderValue,0,255,0,MAX_PWM);

  analogWrite(ENA,speedValue);
  analogWrite(ENB,speedValue);

  server.send(200,"text/plain","OK");
}

// ---------------- GPS HANDLING ----------------

void updateGPS(){
  while(gpsSerial.available()){
    gps.encode(gpsSerial.read());
  }

  if(gps.location.isValid()){
    latitude = String(gps.location.lat(),6);
    longitude = String(gps.location.lng(),6);
  }
}

// ---------------- API ----------------

void getGPS(){
  String data = latitude + "," + longitude;
  server.send(200,"text/plain",data);
}

// ---------------- WEB PAGE ----------------

void gpsPage(){

String page = R"=====(

<!DOCTYPE html>
<html>
<head>
<title>Robot GPS Tracking</title>

<style>
body{
font-family:Arial;
text-align:center;
background:#101010;
color:#00ff90;
}
.box{
margin-top:40px;
padding:25px;
border:2px solid #00ff90;
display:inline-block;
}
button{
padding:10px 20px;
font-size:16px;
background:#00ff90;
border:none;
cursor:pointer;
}
</style>

<script>
function updateGPS(){
fetch("/gps")
.then(r => r.text())
.then(data => {
let coords = data.split(",");
document.getElementById("lat").innerHTML = coords[0];
document.getElementById("lon").innerHTML = coords[1];
document.getElementById("map").href =
"https://maps.google.com/?q="+coords[0]+","+coords[1];
});
}
setInterval(updateGPS,2000);
</script>

</head>

<body onload="updateGPS()">

<h1>🚀 Robot Live GPS Tracking</h1>

<div class="box">

<h2>Latitude</h2>
<h3 id="lat">Loading...</h3>

<h2>Longitude</h2>
<h3 id="lon">Loading...</h3>

<br><br>

<a id="map" target="_blank">
<button>Open in Google Maps</button>
</a>

</div>

</body>
</html>

)=====";

server.send(200,"text/html",page);
}
