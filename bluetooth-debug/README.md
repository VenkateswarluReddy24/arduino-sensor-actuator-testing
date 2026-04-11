# 🔧 Bluetooth Communication Debug Tool (HC-05 / HC-06)

## 📌 Overview
This project is a **Bluetooth communication debugging utility** designed to validate and test serial communication between a mobile device and a microcontroller using HC-05 / HC-06 modules.

It enables developers to verify:
- 📡 Data transmission  
- 🔁 Bidirectional communication  
- 🔢 Command encoding (ASCII level)  

This tool is essential during the development of **Bluetooth-based robotics, IoT systems, and embedded applications**.

---

## 🧠 System Architecture


Mobile App (Bluetooth Terminal)
↓
HC-05 Module
↓
Microcontroller (UART)
↓
Serial Monitor


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno / Nano | 1 |
| HC-05 / HC-06 Bluetooth Module | 1 |
| Jumper Wires | As required |
| Power Supply | 1 |

---

## 🔌 Circuit Connections

| HC-05 Pin | Arduino Pin |
|----------|------------|
| TX | RX (D0) |
| RX | TX (D1) |
| VCC | 5V |
| GND | GND |

⚠️ **Important:**  
Use a voltage divider for HC-05 RX if required (3.3V logic).

---

## ⚙️ Working Principle

1. Mobile app sends character via Bluetooth  
2. HC-05 receives and forwards via UART  
3. Microcontroller reads incoming data  
4. System:
   - Displays received character  
   - Sends echo response  
   - Prints ASCII value  

---

## 🔁 Data Flow


Mobile → Bluetooth → Arduino → Serial Monitor
← Echo Response ←


---

## 💻 Software Implementation

- Platform: Arduino IDE  
- Language: Embedded C/C++  
- Communication Protocol: UART (Serial)  

---

## 🚀 Key Features

- 📡 Real-time Bluetooth data monitoring  
- 🔁 Bidirectional communication testing  
- 🔍 ASCII-level debugging support  
- 🧪 Ideal for system validation  
- ⚡ Lightweight and fast execution  

---

## 📷 Output

### Serial Monitor Output:

[RX] Received: A
[TX] Echo: A
[INFO] ASCII: 65


---

## 🎯 Applications

- Bluetooth robot debugging  
- IoT communication testing  
- Serial protocol validation  
- Embedded system development  
- Wireless control systems  

---

## ⚠️ System Considerations

- Ensure correct baud rate (default: 9600)  
- Verify proper TX/RX connections  
- Avoid conflicts with USB serial during upload  
- Maintain stable power supply  

---

## 🔮 Future Enhancements

- 📱 Custom mobile debugging app  
- 📊 Data logging system  
- 📡 Multi-device communication testing  
- 🔐 Encrypted communication testing  
- 🌐 WiFi + Bluetooth hybrid debugging  

---

## 🧩 Integration Potential

This tool can be integrated into:
- Robotics development workflows  
- IoT testing environments  
- Embedded debugging toolkits  
- Communication protocol analyzers  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Project Highlights

✔ Communication protocol debugging  
✔ Embedded system validation tool  
✔ Bluetooth + UART integration  
✔ Developer-focused utility project  
