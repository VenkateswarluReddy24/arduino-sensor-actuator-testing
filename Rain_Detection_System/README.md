# 🌧️ Automatic Rain Detection & Protection System

## 📌 Overview
This project implements a **smart rain detection system** that automatically protects equipment by closing a cover when rain is detected.

It uses a rain sensor and servo motor to create a **real-time environmental response system**.

---

## 🧠 System Architecture


Rain Sensor → Arduino → Decision Logic → Servo Motor


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno / Nano | 1 |
| Rain Sensor Module | 1 |
| Servo Motor (SG90) | 1 |

---

## 🔌 Connections

| Component | Arduino |
|----------|--------|
| Rain Analog | A0 |
| Rain Digital | D7 |
| Servo | D9 |

---

## ⚙️ Working Principle

- Sensor reads moisture level  
- System filters noise using averaging  
- Confirms rain condition using multiple checks  
- If rain detected:
  - Servo closes protective cover  
- If dry:
  - Servo opens cover  

---

## 🧠 Logic Design

- Multi-sample filtering  
- Threshold-based detection  
- Confirmation mechanism to avoid false triggers  
- State-based actuation  

---

## 🚀 Features

- 🌧️ Real-time rain detection  
- 🧠 Noise filtering  
- 🔁 State-based control  
- ⚙️ Smooth servo movement  
- 🛑 False trigger prevention  

---

## 📷 Output

- Servo closes during rain  
- Servo opens in dry conditions  
- Serial monitor shows system state  

---

## 🎯 Applications

- Smart window systems  
- Automated roof covers  
- Agriculture protection systems  
- Outdoor equipment safety  

---

## ⚠️ Notes

- Sensor requires calibration  
- Avoid direct water accumulation on board  
- Adjust threshold based on environment  

---

## 🔮 Future Enhancements

- IoT alerts (Blynk / Firebase)  
- Weather prediction integration  
- Solar-powered system  
- Smart irrigation linkage  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Environmental automation  
✔ Sensor filtering techniques  
✔ Real-time actuator control  
✔ Practical IoT-ready system  
