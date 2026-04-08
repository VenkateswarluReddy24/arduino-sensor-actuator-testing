# 👆 TTP Touch Sensor Module

## 📌 Description
This module implements reliable touch detection using the TTP touch sensor.  
It is designed as a stable digital input system with debounce handling and event-based detection.

---

## 🔌 Pin Configuration

| Component   | Pin |
|------------|-----|
| Signal OUT | D2  |
| VCC        | 5V  |
| GND        | GND |

---

## ⚙️ Working Principle

- TTP sensor detects touch via capacitive sensing  
- Outputs HIGH when touched  
- Outputs LOW when released  
- Signal is processed with debounce logic  

---

## 💻 Code Logic

1. Read touch sensor state  
2. Apply debounce filtering  
3. Detect state changes  
4. Trigger events:
   - Touch Pressed  
   - Touch Released  

---

## 🚀 Features

- ✅ Debounce handling (stable input)  
- ✅ Touch press/release detection  
- ✅ Event-based architecture  
- ✅ Clean and reusable design  

---

## 📊 Specifications

- Type: Capacitive Touch Sensor  
- Output: Digital (HIGH/LOW)  
- Operating Voltage: 2V – 5.5V  

---

## ⚠️ Notes

- Avoid electrical noise interference  
- Ensure proper grounding  
- Do not touch wiring while testing  

---

## 📷 Output

### Serial Monitor
Displays:
- Touch Detected  
- Touch Released  

### Hardware Setup
(Add your image here)

---

## 🎯 Applications

- Touch-based switches  
- Smart home control panels  
- Human-machine interfaces  
- Interactive systems  

---

## 🧩 Integration

Can be integrated with:
- Relay modules (touch switch)  
- IoT systems (ESP8266/ESP32)  
- Robotics control interfaces  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka
