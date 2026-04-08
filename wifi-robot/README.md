# 🤖 WiFi Controlled Robot (ESP8266 + Mobile App)

## 📌 Overview
This project implements a WiFi-controlled differential drive robot using ESP8266 and a custom mobile application built with MIT App Inventor.

The robot supports real-time directional control and dynamic speed adjustment via a mobile interface.

---

## 🧠 System Architecture

- ESP8266 operates in Access Point (AP) mode  
- Mobile app sends HTTP requests  
- Embedded server processes commands  
- Motor driver executes movement  

---

## 🔌 Hardware Components

- ESP8266 (NodeMCU)
- L298N Motor Driver
- DC Motors (2)
- Robot Chassis
- Power Supply

---

## 📱 Mobile App (MIT App Inventor)

- Direction control buttons:
  - Forward
  - Backward
  - Left
  - Right
  - Stop

- 🎚 Slider for real-time speed control

---

## ⚙️ Features

- ✅ WiFi-based control (no internet required)  
- ✅ Real-time movement control  
- ✅ Dynamic speed control using slider  
- ✅ Modular motor control system  
- ✅ Safety timeout (auto stop)  
- ✅ Low-latency communication  

---

## 🔗 API Endpoints

| Command  | Endpoint   |
|---------|-----------|
| Forward | /forward  |
| Back    | /back     |
| Left    | /left     |
| Right   | /right    |
| Stop    | /stop     |
| Speed   | /speed?value=0-255 |

---

## ⚠️ Safety Features

- Auto-stop if no command received  
- Speed input constrained  
- Stable WiFi (sleep disabled)  

---

## 🎯 Applications

- Robotics control systems  
- Surveillance robots  
- IoT robotics platforms  
- Remote automation  

---

## 🔮 Future Enhancements

- Camera streaming (ESP32-CAM)  
- Obstacle avoidance integration  
- Voice control  
- Cloud-based control  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka
