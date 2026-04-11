# 🔊 Sound Event Detection System (Embedded Interrupt Logic)

## 📌 Overview
This project implements a real-time sound detection system using a digital sound sensor.

The system detects sound events and triggers an LED response using non-blocking logic and debounce filtering.

---

## 🧠 System Architecture

Sound Sensor → Signal Detection → Debounce Filter → Event Trigger → LED Output

---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno | 1 |
| Sound Sensor Module | 1 |
| LED | 1 |

---

## 🔌 Connections

| Component | Arduino |
|----------|--------|
| Sound OUT | D2 |
| LED | D13 |

---

## ⚙️ Working Principle

- Sound sensor outputs LOW when sound is detected  
- System detects falling signal  
- Debounce prevents false triggers  
- LED turns ON for a fixed duration  

---

## 🚀 Features

- 🔊 Real-time sound detection  
- ⚡ Non-blocking execution  
- 🧠 Debounce noise filtering  
- 📊 Serial event logging  

---

## 📷 Output

- LED blinks when sound is detected  
- Serial monitor logs events  

---

## 🎯 Applications

- Clap switch systems  
- Noise monitoring  
- Smart home triggers  
- Security alerts  

---

## 🔮 Future Enhancements

- Relay-based appliance control  
- IoT sound monitoring  
- Threshold-based analog sensing  
- Machine learning sound classification  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Event-driven embedded design  
✔ Noise filtering logic  
✔ Non-blocking system architecture 
