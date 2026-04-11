# 📏 Ultrasonic Distance Measurement System (LCD + Filtering)

## 📌 Overview
This project implements a **high-accuracy distance measurement system** using the HC-SR04 ultrasonic sensor.

A **median filtering algorithm** is applied to reduce noise and improve measurement stability, with results displayed on an LCD.

---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno / Nano | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| 16x2 LCD (I2C) | 1 |

---

## 🔌 Connections

### Ultrasonic Sensor
| Pin | Arduino |
|-----|--------|
| TRIG | D6 |
| ECHO | D7 |

### LCD
| Pin | Arduino |
|-----|--------|
| SDA | A4 |
| SCL | A5 |

---

## ⚙️ Working Principle

- Sensor emits ultrasonic pulse  
- Echo time is measured  
- Distance is calculated  
- Median filter removes noise  
- Result displayed on LCD  

---

## 🧠 Filtering Logic

- 5 samples collected  
- Values sorted  
- Middle value (median) selected  

This improves accuracy in noisy environments.

---

## 🚀 Features

- 📏 Accurate distance measurement  
- 🧠 Median filtering for stability  
- 📟 Real-time LCD display  
- ⚡ Noise-resistant system  

---

## 📷 Output

- LCD displays distance in cm  
- Shows "No Signal" when no echo detected  

---

## 🎯 Applications

- Distance measurement tools  
- Robotics navigation  
- Industrial automation  
- Smart sensing systems  

---

## ⚠️ Notes

- Avoid angled surfaces for accuracy  
- Sensor range ~2cm to 400cm  
- Stable power supply required  

---

## 🔮 Future Enhancements

- Add buzzer for proximity alert  
- IoT data logging  
- Multi-sensor fusion  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Signal filtering implementation  
✔ Sensor accuracy improvement  
✔ Embedded display system  
