# 🌱 IoT-Based Smart Irrigation System (ESP8266 + Blynk)

## 📌 Overview
This project implements an **IoT-enabled smart irrigation system** that automates watering based on real-time soil moisture levels.

The system operates in both **automatic** and **manual modes**, allowing intelligent water management while also giving user control via a mobile application.

This solution is designed to improve water efficiency, reduce manual effort, and enable precision agriculture.

---

## 🧠 System Architecture

The system is structured into three layers:

### 1. 🌿 Sensing Layer
- Soil moisture sensor measures water content in soil  
- Analog signal is converted into digital values  

### 2. ⚙️ Control Layer (ESP8266)
- Processes sensor data  
- Applies control logic (AUTO / MANUAL mode)  
- Controls water pump via relay  

### 3. 📱 Cloud & Interface Layer (Blynk IoT)
- Displays real-time soil data  
- Allows remote control of irrigation system  
- Enables mode switching  

---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| ESP8266 (NodeMCU) | 1 |
| Soil Moisture Sensor | 1 |
| Relay Module | 1 |
| Water Pump / Motor | 1 |
| Jumper Wires | As required |
| Power Supply | 1 |

---

## 🔌 Circuit Connections

| Component | ESP8266 Pin |
|----------|------------|
| Soil Sensor (AO) | A0 |
| Relay Input | D1 |
| VCC | 3.3V / 5V |
| GND | GND |

⚠️ Note: Relay is **Active LOW**

---

## 📱 Blynk Configuration

| Function | Virtual Pin |
|---------|------------|
| Mode Selection (Auto/Manual) | V0 |
| Pump Control (Manual) | V1 |
| Soil Moisture (%) | V3 |
| Raw Sensor Value | V4 |

---

## ⚙️ Working Principle

### 🔹 Automatic Mode
- System continuously monitors soil moisture  
- If moisture falls below threshold:
  - Pump turns ON  
- When moisture is sufficient:
  - Pump turns OFF  

### 🔹 Manual Mode
- User directly controls pump via Blynk app  
- Overrides automatic logic  

---

## 🧠 Control Logic


IF (mode == AUTO)
IF (soil < threshold)
→ Pump ON
ELSE
→ Pump OFF

IF (mode == MANUAL)
Pump = User Input


---

## 💻 Software Implementation

- Platform: Arduino IDE  
- Language: Embedded C++  
- Libraries:
  - ESP8266WiFi  
  - Blynk  

---

## 🚀 Features

- ✅ Dual mode operation (AUTO + MANUAL)  
- ✅ Real-time soil moisture monitoring  
- ✅ Remote control via mobile app  
- ✅ Noise-filtered sensor readings  
- ✅ Non-blocking execution using millis()  
- ✅ Scalable architecture for multiple zones  

---

## 📊 Data Processing

- Sensor readings are averaged to reduce noise  
- Moisture percentage is calculated using mapping  
- Threshold-based decision making  

---

## 📷 Output

### System Behavior:
- Automatically waters plants when soil is dry  
- Stops watering when sufficient moisture is detected  

### Mobile Interface:
- Real-time soil moisture display  
- Remote pump control  

(Add your project images here)

---

## 🎯 Applications

- Smart agriculture systems  
- Home gardening automation  
- Greenhouse irrigation  
- Water conservation systems  
- Precision farming  

---

## ⚠️ Safety & Notes

- Use proper relay module for pump control  
- Ensure stable power supply  
- Avoid running pump dry  
- Calibrate sensor for accurate readings  

---

## 🔮 Future Enhancements

- 🌐 Weather-based irrigation control  
- 📊 Data logging & analytics  
- 📡 MQTT / Cloud dashboard integration  
- 🌱 Multi-zone irrigation system  
- ⚡ Solar-powered irrigation  

---

## 🧩 Integration Potential

This system can be integrated with:
- Weather APIs  
- Smart home systems  
- Agricultural monitoring platforms  
- AI-based irrigation optimization  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka
