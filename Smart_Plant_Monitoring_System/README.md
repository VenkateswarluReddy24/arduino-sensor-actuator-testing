# 🌱 Smart Plant Monitoring System (Emotion-Based AI)

## 📌 Overview
This project implements an intelligent plant monitoring system using multiple sensors and an emotion-based feedback system.

The system evaluates plant health using soil moisture, temperature, and ambient light, and visually represents the plant’s condition using LED matrix emojis.

---

## 🧠 System Architecture

Sensors → Microcontroller → Emotion Engine → Display (LCD + LED Matrix)

---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno | 1 |
| Capacitive Soil Moisture Sensor | 1 |
| DHT11 Temperature Sensor | 1 |
| LDR Module | 1 |
| MAX7219 LED Matrix | 1 |
| 16x2 LCD (I2C) | 1 |

---

## 🔌 Connections

### Sensors
- Soil Sensor → A0  
- LDR → D5  
- DHT11 → D9  

### LED Matrix
- DIN → D11  
- CLK → D13  
- CS → D10  

### LCD
- SDA → A4  
- SCL → A5  

---

## ⚙️ Working Principle

- Soil moisture determines hydration level  
- Temperature detects heat stress  
- LDR detects day/night condition  
- System assigns plant “emotion”  
- Displays:
  - Emoji (LED Matrix)
  - Status (LCD)

---

## 😊 Emotion States

| State | Condition |
|------|----------|
| 😊 Healthy | Optimal moisture |
| 😢 Dry | Water required |
| 🔥 Hot | Temperature stress |
| 😴 Sleep | Night condition |

---

## 🚀 Features

- 🌱 Multi-sensor integration  
- 🧠 Intelligent decision system  
- 🎭 Visual emotion feedback  
- 📟 Dual display system  
- ⚡ Real-time monitoring  

---

## 🎯 Applications

- Smart agriculture  
- Indoor plant monitoring  
- IoT plant health systems  
- Educational robotics  

---

## 🔮 Future Enhancements

- IoT dashboard (Blynk/Firebase)  
- Auto irrigation system  
- Mobile alerts  
- AI-based prediction  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Multi-sensor fusion  
✔ Embedded decision system  
✔ Human-like interaction (emotion AI)  
✔ Industry-level design thinking  
