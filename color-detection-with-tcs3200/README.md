
# 🎨 Color Detection System using TCS3200 (Embedded Vision Module)

## 📌 Overview
This project implements a **color detection system** using the TCS3200 color sensor.

The system identifies four colors:
- 🔴 Red  
- 🟢 Green  
- 🔵 Blue  
- ⚪ White  

Detected color is displayed on an LCD and indicated using an RGB LED.

---

## 🧠 System Architecture


Object → TCS3200 Sensor → Arduino → LCD + RGB LED


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno / Nano | 1 |
| TCS3200 Color Sensor | 1 |
| 16x2 LCD (I2C) | 1 |
| RGB LED | 1 |
| Resistors | 3 |
| Jumper Wires | As required |

---

## 🔌 Circuit Connections

### TCS3200
| Pin | Arduino |
|-----|--------|
| S0 | D4 |
| S1 | D5 |
| S2 | D6 |
| S3 | D7 |
| OUT | D2 |
| OE | D8 |

### RGB LED
| Color | Arduino |
|------|--------|
| Red | D9 |
| Green | D11 |
| Blue | D10 |

### LCD
| LCD | Arduino |
|-----|--------|
| SDA | A4 |
| SCL | A5 |

---

## ⚙️ Working Principle

- Sensor outputs frequency based on color intensity  
- Microcontroller reads RGB values  
- Decision logic compares intensities  
- Identifies dominant color  
- Displays result on LCD  
- Lights corresponding RGB LED  

---

## 🧠 Detection Logic

- Minimum frequency → Dominant color  
- Close RGB values → White detection  
- High values → No object  

---

## 🚀 Features

- Real-time color detection  
- Multi-color classification  
- Visual + display feedback  
- Stable detection logic  

---

## 📷 Output

- LCD shows detected color  
- RGB LED reflects detected color  

---

## 🎯 Applications

- Color sorting systems  
- Industrial automation  
- Object classification  
- Smart robotics  

---

## ⚠️ Notes

- Proper lighting required  
- Calibration improves accuracy  
- Distance affects detection  

---

## 🔮 Future Enhancements

- Add more colors  
- Machine learning classification  
- Conveyor belt sorting system  
- IoT monitoring  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Embedded sensor processing  
✔ Real-time classification  
✔ Hardware + logic integration  
✔ Industrial application potential  
