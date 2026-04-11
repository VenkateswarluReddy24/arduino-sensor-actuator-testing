# 📡 Signal Detection System (Frequency Tuner Simulator)

## 📌 Overview
This project simulates a **signal detection system** using a potentiometer as a frequency tuning input.

The system detects when the tuned frequency matches a predefined target and provides:
- 📟 LCD feedback  
- 💡 LED indication  
- 🔊 Audio signal  

---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno / Nano | 1 |
| Potentiometer | 1 |
| 16x2 LCD (I2C) | 1 |
| Buzzer | 1 |
| LED | 1 |

---

## 🔌 Connections

| Component | Arduino |
|----------|--------|
| Potentiometer | A0 |
| Buzzer | D5 |
| LED | D3 |
| LCD SDA | A4 |
| LCD SCL | A5 |

---

## ⚙️ Working Principle

- Potentiometer adjusts frequency value  
- System compares with target frequency  
- Based on difference:
  - 🎯 Match → Signal Found  
  - 🔍 Near → Searching  
  - ❌ Far → No Signal  

---

## 🚀 Features

- Real-time frequency tuning  
- Multi-level signal detection  
- Audio + visual feedback  
- Smooth user interaction  

---

## 📷 Output

- LCD shows frequency and status  
- LED and buzzer indicate signal strength  

---

## 🎯 Applications

- Frequency tuning simulation  
- Embedded UI design  
- Signal processing learning  
- Control system visualization  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Analog signal processing  
✔ Embedded UI system  
✔ Real-time feedback control  
