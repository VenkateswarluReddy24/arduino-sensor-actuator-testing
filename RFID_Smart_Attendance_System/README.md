# 📡 RFID Smart Attendance System (ESP8266 + Google Sheets)

## 📌 Overview
This project implements a **cloud-connected RFID attendance system** using ESP8266.

It reads RFID cards, identifies users, and logs attendance directly into **Google Sheets in real time**.

---

## 🧠 System Architecture


RFID Card → ESP8266 → WiFi → Google Sheets (Cloud)


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| ESP8266 (NodeMCU) | 1 |
| MFRC522 RFID Module | 1 |
| RFID Cards/Tags | Multiple |

---

## 🔌 Connections

| MFRC522 | ESP8266 |
|--------|--------|
| SDA | D4 |
| RST | D3 |
| MOSI | D7 |
| MISO | D6 |
| SCK | D5 |

---

## ⚙️ Working Principle

1. RFID card is scanned  
2. UID is read and processed  
3. Student is identified  
4. Data is sent to Google Sheets  
5. Attendance is logged in real time  

---

## 🚀 Features

- 📡 Real-time cloud logging  
- 🔐 Secure credential handling  
- 🧠 UID-based identification  
- ⚡ Fast response system  
- 📊 Google Sheets integration  

---

## 📷 Output

- Serial Monitor:
  - UID detection  
  - Student identification  
  - HTTP response  

- Google Sheets:
  - Name  
  - UID  
  - Section  

---

## 🎯 Applications

- Smart attendance systems  
- Access control systems  
- Office entry logging  
- Industrial tracking systems  

---

## ⚠️ Security Note

Sensitive data (WiFi & API URL) is stored in `config.h` and excluded from GitHub.

---

## 🔮 Future Enhancements

- Face recognition integration  
- Mobile app dashboard  
- Firebase integration  
- Offline storage backup  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ IoT + RFID integration  
✔ Cloud-based system  
✔ Real-time data logging  
✔ Industry-level application  
