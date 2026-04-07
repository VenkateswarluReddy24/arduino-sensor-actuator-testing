# 🚦 Smart Traffic Light Control System

## 📌 Overview
This project implements a **dual-road smart traffic light control system** using Arduino Nano and a TM1637 4-digit display.

The system manages traffic flow between two roads using timed signal transitions and a real-time countdown display, simulating a basic intelligent traffic controller used in urban environments.

---

## 🧠 System Architecture

The system is designed with a modular approach:
- Each road is treated as an independent traffic unit
- Central logic controls signal transitions
- Countdown timer provides real-time feedback

---

## 🔌 Hardware Components

- Arduino Nano (with Expansion Board)
- 2 × Traffic Light LED Modules (Red, Yellow, Green)
- TM1637 4-Digit Display Module
- Jumper Wires
- Power Supply (5V)

---

## 🔗 Pin Configuration

### TM1637 Display
| Component | Pin |
|----------|-----|
| CLK      | D2  |
| DIO      | D4  |

### Traffic Light – Road 1
| Signal | Pin |
|--------|-----|
| Red    | D10 |
| Yellow | D13 |
| Green  | D12 |

### Traffic Light – Road 2
| Signal | Pin |
|--------|-----|
| Red    | D6  |
| Yellow | D3  |
| Green  | D9  |

---

## ⚙️ Working Principle

1. Road 1 is set to GREEN while Road 2 remains RED  
2. Countdown timer displays remaining time  
3. Road 1 transitions to YELLOW before stopping  
4. Road 2 switches to GREEN  
5. Process repeats continuously  

The system ensures:
- No signal conflicts  
- Smooth transitions  
- Clear visual timing feedback  

---

## 💻 Code Logic

- Traffic lights are abstracted using structured data (modular design)
- State transitions are handled through a central control function
- Countdown timer updates every second using TM1637 display
- Serial monitor logs real-time system status

---

## 🚀 Features

- ✅ Dual-road traffic control system  
- ✅ Real-time countdown display  
- ✅ Modular and scalable architecture  
- ✅ Clean and maintainable code structure  
- ✅ Serial monitoring for debugging  

---

## 📊 System Specifications

- Microcontroller: Arduino Nano  
- Operating Voltage: 5V  
- Display: TM1637 (4-digit 7-segment)  
- Control Type: Time-based sequencing  

---

## ⚠️ Safety & Notes

- Ensure proper current limiting resistors for LEDs  
- Use stable 5V power supply  
- Avoid short circuits on expansion board  
- Verify pin connections before powering  

---

## 📷 Output

### Display Output
- Shows countdown for active signal  

### Traffic Operation
- Alternating traffic flow between two roads  

### Hardware Setup
(Add your real project images here)

---

## 🎯 Applications

- Smart traffic signal systems  
- Educational simulation of traffic control  
- Embedded systems learning  
- Prototype for smart city solutions  

---

## 🔮 Future Enhancements

- 🚗 Traffic density detection using sensors  
- 🚑 Emergency vehicle priority system  
- 📡 IoT-based remote monitoring (ESP8266/ESP32)  
- ⏱ Dynamic signal timing based on traffic conditions  

---

## 🧩 Integration Potential

This system can be extended with:
- Ultrasonic / IR sensors for vehicle detection  
- RFID for priority access  
- Cloud platforms for real-time monitoring  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka
