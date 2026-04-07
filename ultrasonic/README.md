# 📏 Ultrasonic Sensor Module (HC-SR04)

## 📌 Description
This module implements precise distance measurement using the HC-SR04 ultrasonic sensor.  
It is designed as a **reliable and reusable component** for robotics and embedded systems.

---

## 🔌 Pin Configuration

| Component | Pin |
|----------|-----|
| VCC      | 5V  |
| GND      | GND |
| TRIG     | D6  |
| ECHO     | D7  |

---

## ⚙️ Working Principle

1. The TRIG pin sends a 10µs ultrasonic pulse  
2. The sound wave travels through air  
3. The object reflects the wave back  
4. The ECHO pin measures return time  
5. Distance is calculated using time delay  

---

## 🧠 Distance Calculation

Distance is calculated using:

Distance = (Time × Speed of Sound) / 2

Where:
- Speed of sound = **0.0343 cm/µs**
- Time = duration of echo pulse

---

## 💻 Code Logic

1. Send trigger pulse to sensor  
2. Measure echo duration using `pulseIn()`  
3. Convert time to distance  
4. Take multiple samples for stability  
5. Filter invalid readings  
6. Print final averaged distance  

---

## 🚀 Features

- ✅ Multi-sample averaging (noise reduction)  
- ✅ Timeout handling (prevents blocking)  
- ✅ Filtering of invalid readings  
- ✅ Configurable parameters  
- ✅ Clean and readable output  

---

## 📊 Sensor Specifications

- Range: **2 cm – 400 cm**  
- Accuracy: ~3mm  
- Operating Voltage: 5V  

---

## ⚠️ Notes

- Avoid soft surfaces (cloth) — they absorb sound  
- Keep sensor stable for accurate readings  
- Ensure proper power supply (5V recommended)  
- Do not exceed maximum range  

---

## 📷 Output

### Serial Monitor Output
Displays real-time distance in centimeters.

### Hardware Setup
(Add your circuit image here)

---

## 🎯 Applications

- Obstacle avoiding robots  
- Distance measurement systems  
- Smart parking systems  
- Automation and safety systems  

---

## 🧩 Integration

This module is designed to be easily integrated into:
- Robotics navigation systems  
- IoT-based monitoring projects  
- Automation workflows  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka
