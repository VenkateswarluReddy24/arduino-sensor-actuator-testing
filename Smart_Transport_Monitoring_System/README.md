# 🚌 Smart Transport Monitoring System (RFID + Telegram IoT)

## 📌 Overview
This project implements a real-time student tracking system for school transportation using RFID and Telegram notifications.

Each scan logs student activity (boarding/returning) and sends instant alerts to guardians or administrators.

---

## 🧠 System Architecture

RFID → ESP8266 → WiFi → Telegram Bot → User Notification

---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| ESP8266 (NodeMCU) | 1 |
| MFRC522 RFID Module | 1 |
| RFID Cards | Multiple |

---

## 🔌 Connections

| RFID | ESP8266 |
|------|--------|
| SDA | D2 |
| RST | D1 |
| MOSI | D7 |
| MISO | D6 |
| SCK | D5 |

---

## ⚙️ Working Principle

- Student scans RFID card  
- UID is matched with database  
- System determines status:
  - Boarding  
  - Returning  
- Telegram message is sent  
- Unknown cards trigger security alert  

---

## 🚀 Features

- 📡 Real-time notifications  
- 🧠 State-based tracking  
- ⏱ Timestamp logging (NTP)  
- 🚨 Security alerts  
- 🔐 Duplicate scan protection  

---

## 📷 Output

Telegram message includes:
- Bus ID  
- Student Name  
- Status  
- Time  

---

## 🎯 Applications

- School transport monitoring  
- Employee tracking systems  
- Fleet management  
- IoT-based security  

---

## ⚠️ Security Note

Sensitive credentials are stored in `config.h` and excluded from GitHub.

---

## 🔮 Future Enhancements

- GPS tracking integration  
- Mobile app dashboard  
- Cloud database (Firebase)  
- Attendance analytics  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ IoT + Messaging integration  
✔ Real-time monitoring system  
✔ Security-focused design  
✔ Industry-level architecture  
