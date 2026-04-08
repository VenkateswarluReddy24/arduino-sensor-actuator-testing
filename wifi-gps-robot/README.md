# 🤖 WiFi Controlled Robot with Real-Time GPS Tracking

## 📌 Overview
This project implements a **WiFi-controlled differential drive robot** integrated with **real-time GPS tracking** and a **web-based monitoring system**.

The robot can be controlled using a custom mobile application (MIT App Inventor), while simultaneously transmitting its live location to a web dashboard that allows tracking via Google Maps.

---

## 🧠 System Architecture

The system is divided into three core modules:

### 1. 🚗 Motion Control System
- Controls robot movement using HTTP commands
- Supports forward, backward, left, right, and stop operations

### 2. 📡 GPS Tracking System
- Reads real-time coordinates using GPS module
- Processes latitude and longitude using TinyGPS++

### 3. 🌐 Web Monitoring System
- Displays live GPS data on a web page
- Provides direct Google Maps redirection

---

## 🔌 Hardware Components

- ESP8266 (NodeMCU)
- L298N Motor Driver
- 2 × DC Motors (Differential Drive)
- GPS Module (NEO-6M or similar)
- Robot Chassis
- Power Supply (Battery)

---

## 🔗 Pin Configuration

### Motor Driver (L298N)

| ESP8266 | L298N |
|--------|------|
| D1 | IN1 |
| D2 | IN2 |
| D5 | IN3 |
| D6 | IN4 |
| D7 | ENA |
| D8 | ENB |

---

### GPS Module

| GPS Module | ESP8266 |
|-----------|--------|
| TX        | D3     |
| RX        | D4     |
| VCC       | 3.3V / 5V |
| GND       | GND    |

---

## 📱 Mobile App (MIT App Inventor)

The robot is controlled using a custom-built mobile application.

### Features:
- Direction buttons:
  - Forward
  - Backward
  - Left
  - Right
  - Stop
- 🎚 Slider for real-time speed control

### Communication:
- Sends HTTP requests to ESP8266 server

---

## 🌐 Web Dashboard

Access via:http://192.168.4.1/

### Features:
- Live latitude & longitude display
- Auto-refresh every 2 seconds
- One-click Google Maps navigation

---

## 🔗 API Endpoints

| Function  | Endpoint |
|----------|---------|
| Forward  | /forward |
| Backward | /back |
| Left     | /left |
| Right    | /right |
| Stop     | /stop |
| Speed    | /speed?value=0-255 |
| GPS Data | /gps |

---

## ⚙️ Working Principle

1. ESP8266 creates a WiFi Access Point  
2. Mobile app connects and sends control commands  
3. Robot executes movement using motor driver  
4. GPS module continuously updates location  
5. Web server displays live coordinates  
6. User can track robot on Google Maps  

---

## 🚀 Features

- ✅ WiFi-based robot control (no internet required)  
- ✅ Real-time GPS tracking  
- ✅ Integrated web dashboard  
- ✅ Mobile app control (MIT App Inventor)  
- ✅ Dynamic speed control  
- ✅ Low-latency communication  

---

## ⚠️ Safety & Notes

- Use external power supply for motors  
- Ensure GPS module has clear sky view  
- Avoid powering GPS directly from unstable sources  
- Verify correct pin connections before operation  

---

## 📷 Output

### Robot Control
- Real-time movement via mobile app  

### GPS Tracking
- Live location displayed on webpage  

### Google Maps Integration
- One-click navigation to robot location  

(Add your images and screenshots here)

---

## 🎯 Applications

- Surveillance robots  
- Search and rescue systems  
- Asset tracking systems  
- Outdoor robotics navigation  
- IoT-enabled robotics  

---

## 🔮 Future Enhancements

- 📷 Live video streaming (ESP32-CAM)  
- 🧠 Autonomous navigation (AI/ML)  
- ☁️ Cloud-based tracking (Firebase, Thingspeak)  
- 🎤 Voice-controlled robot  
- 🚧 Obstacle avoidance integration  

---

## 🧩 Integration Potential

This system can be extended with:
- Ultrasonic sensors for obstacle detection  
- RFID for access control  
- IoT dashboards for remote monitoring  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka
