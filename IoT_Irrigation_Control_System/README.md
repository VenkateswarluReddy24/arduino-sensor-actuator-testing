# 💧 IoT Smart Irrigation Control System (Blynk + ESP8266)

## 📌 Overview
This project implements a **remote irrigation control system** using ESP8266 and the Blynk IoT platform.

The system allows users to control a water pump (relay) remotely via a mobile app.

---

## 🧠 System Architecture


Mobile App → Blynk Cloud → ESP8266 → Relay → Water Pump


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| ESP8266 (NodeMCU) | 1 |
| Relay Module | 1 |
| Water Pump | 1 |

---

## 🔌 Connections

| Component | ESP8266 |
|----------|--------|
| Relay IN | D5 |
| VCC | 5V |
| GND | GND |

---

## ⚙️ Working Principle

- User toggles switch in Blynk app  
- Command sent via cloud  
- ESP8266 receives signal  
- Relay turns ON/OFF  
- Pump is controlled remotely  

---

## 🚀 Features

- 📡 Remote irrigation control  
- ⚡ Real-time response  
- 🔐 Secure credential management  
- 📱 Mobile app integration  

---

## 📷 Output

- Pump turns ON/OFF via mobile  
- Serial monitor shows relay state  

---

## 🎯 Applications

- Smart agriculture  
- Home gardening automation  
- Water management systems  

---

## ⚠️ Security Note

Sensitive credentials are stored in `config.h` and excluded using `.gitignore`.

---

## 🔮 Future Enhancements

- Soil moisture automation  
- Weather-based irrigation  
- IoT analytics dashboard  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ IoT control system  
✔ Cloud-based automation  
✔ Embedded + mobile integration  
