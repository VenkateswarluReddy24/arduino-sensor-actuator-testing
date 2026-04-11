# 🌱 Capacitive Soil Moisture Sensor (Smart Test Module)

## 📌 Overview
This project demonstrates a **capacitive soil moisture sensor interface** using an Arduino-compatible microcontroller.

It reads soil moisture levels and converts raw analog values into a **meaningful percentage**, enabling quick calibration and testing for irrigation and environmental monitoring systems.

---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno / Nano | 1 |
| Capacitive Soil Moisture Sensor | 1 |
| Jumper Wires | As required |

---

## 🔌 Circuit Connection

| Sensor Pin | Arduino |
|-----------|--------|
| AOUT | A0 |
| VCC | 5V |
| GND | GND |

---

## ⚙️ Working Principle

- Sensor outputs an **analog value based on soil moisture**
- Higher value → Dry soil  
- Lower value → Wet soil  

The system maps raw readings into a **percentage (0–100%)**:


Moisture (%) = map(raw_value, dry, wet)


---

## 💻 Software Implementation

- Platform: Arduino IDE  
- Language: Embedded C/C++  
- Communication: Serial Monitor  

---

## 🚀 Key Features

- 🌱 Real-time moisture sensing  
- 📊 Percentage-based output  
- ⚙️ Calibration-ready design  
- ⚡ Lightweight and efficient  

---

## 📷 Output


Raw: 650 | Moisture: 42%
Raw: 720 | Moisture: 30%


---

## 🎯 Applications

- Smart irrigation systems  
- Agriculture monitoring  
- Plant care automation  
- Environmental sensing  

---

## ⚠️ Notes

- Calibration is required for accurate results  
- Avoid direct water exposure on sensor electronics  
- Values vary based on soil type  

---

## 🔮 Future Scope

- Relay-based automatic irrigation  
- IoT integration (Blynk / Firebase)  
- Multi-sensor soil monitoring  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Sensor calibration understanding  
✔ Analog data processing  
✔ Clean embedded implementation  
