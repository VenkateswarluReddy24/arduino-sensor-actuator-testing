# 🐾 Automated Pet Feeder (Timer-Based System)

## 📌 Overview
This project implements an automated pet feeding system using Arduino, a servo motor, and a TM1637 display.

The system dispenses food at fixed time intervals using a controlled mechanical actuator.

---

## 🧠 System Architecture

- Timer module controls feeding intervals  
- Servo motor acts as dispensing mechanism  
- Display shows countdown to next feed  

---

## 🔌 Hardware Components

- Arduino UNO  
- SG90 Servo Motor  
- TM1637 Display Module  
- Power Supply  

---

## 🔗 Pin Configuration

### TM1637 Display
| Component | Pin |
|----------|-----|
| CLK      | D3  |
| DIO      | D2  |

### Servo Motor
| Component | Pin |
|----------|-----|
| Signal   | D9  |
| VCC      | 5V  |
| GND      | GND |

---

## ⚙️ Working Principle

1. System starts countdown timer  
2. Display shows remaining time  
3. When timer reaches zero:
   - Servo rotates to dispense food  
   - Waits for dispensing duration  
   - Returns to closed position  
4. Timer resets and repeats  

---

## 🚀 Features

- ✅ Automated feeding system  
- ✅ Real-time countdown display  
- ✅ Smooth servo actuation  
- ✅ Configurable feeding interval  
- ✅ Modular and scalable design  

---

## 📊 Specifications

- Feeding Interval: Configurable (default 20s)  
- Servo Range: 0°–90°  
- Display: 4-digit TM1637  

---

## ⚠️ Notes

- Use stable power supply for servo  
- Avoid overloading servo mechanism  
- Ensure proper food dispensing path  

---

## 📷 Output

- Countdown timer display  
- Automatic food dispensing  

(Add your images here)

---

## 🎯 Applications

- Pet care automation  
- Smart home systems  
- Timed dispensing systems  

---

## 🔮 Future Enhancements

- 📱 Mobile app control  
- 📡 IoT monitoring  
- ⏰ RTC-based real-time feeding schedule  
- ⚖️ Weight-based dispensing  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka
