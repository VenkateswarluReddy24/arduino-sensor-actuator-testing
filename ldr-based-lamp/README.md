# 🔦 Automatic Night Lamp using LDR (LM393 Comparator)

## 📌 Overview
This project implements an automatic lighting control system using an LDR (Light Dependent Resistor) module with an onboard LM393 comparator.

The system detects ambient light conditions and automatically controls an LED, enabling energy-efficient lighting without manual intervention.

- 🌙 LED turns ON in darkness  
- ☀️ LED turns OFF in bright light  

This project demonstrates sensor interfacing, digital signal processing, and automation logic in embedded systems.

---

## 🧠 System Architecture

The system consists of three core components:

### 1. 🌗 Light Sensing Unit
- LDR detects ambient light intensity  
- LM393 comparator converts analog signal into digital output  

### 2. ⚙️ Control Unit
- Microcontroller reads digital signal  
- Applies decision logic  

### 3. 💡 Output Unit
- LED acts as an indicator / lighting element  

---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino UNO / NodeMCU | 1 |
| LDR Module (LM393) | 1 |
| LED | 1 |
| Resistor (220Ω) | 1 |
| Breadboard | 1 |
| Jumper Wires | As required |

---

## 🔌 Circuit Connections

| Component | Connection |
|----------|-----------|
| LDR DO   | Digital Pin 7 |
| LED (+)  | Digital Pin 8 |
| LED (-)  | GND |
| VCC      | 5V |
| GND      | GND |

---

## ⚙️ Working Principle

- The LDR senses light intensity  
- The LM393 comparator compares it with a threshold set using a potentiometer  
- Outputs a digital signal:

| Condition | Output |
|----------|--------|
| Darkness | HIGH |
| Bright Light | LOW |

- The microcontroller reads this signal and controls the LED accordingly  

---

## 🧠 Embedded Logic


IF (LDR == HIGH)
→ Darkness detected
→ LED ON
ELSE
→ Bright environment
→ LED OFF


---

## 💻 Software Implementation

- Language: Embedded C (Arduino Framework)  
- Platform: Arduino IDE  
- Input Type: Digital (Comparator Output)  
- Debugging: Serial Monitor  

---

## 🚀 Features

- Automatic light detection  
- Adjustable sensitivity using onboard potentiometer  
- Real-time response  
- Low power consumption  
- Simple and scalable design  

---

## 📷 Output

- LED automatically turns ON in dark conditions  
- LED turns OFF in bright conditions  

(Add your hardware images here)

---

## 🔍 Applications

- Smart street lighting systems  
- Automatic home lighting  
- Energy-saving automation systems  
- Industrial safety indicators  
- Outdoor lighting control  

---

## 📈 Future Enhancements

- Replace LED with relay for AC appliances  
- Integrate IoT (Blynk / MQTT)  
- Add motion detection (PIR sensor)  
- Use analog reading for adaptive threshold control  
- Cloud-based monitoring system  

---

## 🧩 Integration Potential

This module can be integrated with:
- Smart home automation systems  
- IoT-based lighting control  
- Security systems  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka
