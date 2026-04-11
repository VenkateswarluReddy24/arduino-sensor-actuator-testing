# 🌡️ IoT Temperature & Humidity Monitoring System (Blynk + ESP8266)

## 📌 Overview
This project implements a **real-time IoT-based environmental monitoring system** using the ESP8266 and DHT sensor.

The system measures:
- 🌡️ Temperature  
- 💧 Humidity  

and transmits data to the **Blynk IoT cloud platform** for remote monitoring.

---

## 🧠 System Architecture


DHT Sensor → ESP8266 → WiFi → Blynk Cloud → Mobile App


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| ESP8266 (NodeMCU / D1 Mini) | 1 |
| DHT11 / DHT22 Sensor | 1 |
| Jumper Wires | As required |

---

## 🔌 Circuit Connections

| Sensor Pin | ESP8266 |
|-----------|--------|
| DATA | D4 |
| VCC | 3.3V |
| GND | GND |

---

## ⚙️ Working Principle

1. Sensor reads temperature & humidity  
2. ESP8266 processes data  
3. Data is sent to Blynk cloud  
4. User monitors data via mobile app  

---

## 💻 Software Implementation

- Platform: Arduino IDE  
- Language: Embedded C/C++  
- Libraries:
  - Blynk  
  - DHT  

---

## 🚀 Key Features

- 📡 Real-time IoT monitoring  
- 🌐 Cloud integration (Blynk)  
- ⚡ Non-blocking architecture  
- 🔐 Secure credential management  
- 📊 Live dashboard visualization  

---

## 📷 Output

- Mobile app displays:
  - Temperature (°C)
  - Humidity (%)

---

## 🎯 Applications

- Smart homes  
- Weather monitoring systems  
- Greenhouse monitoring  
- Industrial environment tracking  

---

## ⚠️ Security Note

Sensitive credentials (WiFi & Blynk tokens) are stored in a separate file (`config.h`) and excluded using `.gitignore`.

---

## 🔮 Future Enhancements

- 📊 Data logging (Firebase / ThingsBoard)  
- 📱 Alerts & notifications  
- 🌡️ Multi-sensor integration  
- 🤖 Automation triggers  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ IoT system design  
✔ Cloud integration  
✔ Secure coding practices  
✔ Real-time data monitoring 
