# 📡 ESP8266 WiFi Network Analyzer

## 📌 Overview
This project implements a real-time WiFi network analyzer using ESP8266.

It scans nearby wireless networks and provides detailed diagnostics such as signal strength, security type, and channel information.

---

## 🧠 System Architecture

ESP8266 → WiFi Scan Engine → Data Processing → Serial Output

---

## ⚙️ Features

- 🔍 Continuous WiFi scanning  
- 📶 Signal strength classification  
- 🔐 Encryption type detection  
- 📡 Channel monitoring  
- ⚡ Non-blocking architecture  

---

## 🛠️ Hardware

| Component | Quantity |
|----------|---------|
| ESP8266 (NodeMCU) | 1 |

---

## 💻 Software

- Arduino IDE (ESP8266 Core)

---

## 🚀 Working Principle

- Device enters station mode  
- Periodically scans nearby networks  
- Extracts:
  - SSID
  - RSSI (signal strength)
  - Encryption type
  - Channel  
- Displays structured output via Serial Monitor  

---

## 📊 Output Example

SSID: ATL LAB | RSSI: -52 dBm | Quality: Good | Security: WPA2 | Channel: 6

---

## 📈 Signal Quality Mapping

| RSSI (dBm) | Quality |
|----------|--------|
| > -50 | Excellent |
| -60 to -50 | Good |
| -70 to -60 | Fair |
| < -70 | Weak |

---

## 🎯 Applications

- Network analysis  
- IoT deployment planning  
- Signal optimization  
- Wireless debugging  

---

## 🔮 Future Enhancements

- OLED display integration  
- Web dashboard  
- Signal heat mapping  
- Auto channel recommendation  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Real-time WiFi diagnostics  
✔ Embedded network analysis tool  
✔ Industry-style structured output  
✔ Useful for IoT deployment planning  
