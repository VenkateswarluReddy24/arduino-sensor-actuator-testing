# 📡 RFID Module (RC522) - Access Control System

## 📌 Description
This module implements RFID-based identification using the RC522 reader.  
It supports UID detection and authorization logic, forming the base for secure access systems.

---

## 🔌 Pin Configuration

| RC522 Pin | Arduino UNO |
|----------|------------|
| SDA (SS) | D10        |
| SCK      | D13        |
| MOSI     | D11        |
| MISO     | D12        |
| RST      | D9         |
| GND      | GND        |
| 3.3V     | 3.3V       |

⚠️ Use **3.3V only**, NOT 5V

---

## ⚙️ Working Principle

1. RFID reader emits electromagnetic signal  
2. RFID card enters field  
3. Card transmits UID  
4. System reads UID  
5. UID is validated against stored data  

---

## 💻 Code Logic

1. Initialize SPI and RFID module  
2. Detect new card  
3. Read UID from card  
4. Convert UID to readable format  
5. Compare with authorized UID  
6. Display access result  

---

## 🚀 Features

- ✅ UID detection and formatting  
- ✅ Authorization system (Access Control)  
- ✅ Clean and reusable function design  
- ✅ Expandable for IoT/Database integration  

---

## 📊 Specifications

- Frequency: 13.56 MHz  
- Communication: SPI  
- Operating Voltage: 3.3V  

---

## ⚠️ Notes

- Do NOT connect to 5V (can damage module)  
- Keep card within 3–5 cm range  
- Avoid metal interference  

---

## 📷 Output

### Serial Monitor
Displays:
- Card UID  
- Access Granted / Denied  

### Hardware Setup
(Add your image here)

---

## 🎯 Applications

- RFID Attendance Systems  
- Smart Door Lock Systems  
- Access Control Systems  
- Inventory Tracking  

---

## 🧩 Integration

This module can be integrated with:
- ESP8266 / ESP32 (IoT systems)  
- Telegram / Blynk  
- Databases for logging  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka
