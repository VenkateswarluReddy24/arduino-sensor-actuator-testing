# 🔥 Industrial Fire & Gas Alert System (IoT + SMTP + ESP8266)

## 📌 Overview
This project implements an **Industrial Fire & Gas Alert System** designed for factory environments and safety-critical applications.

The system continuously monitors gas levels using an MQ-2 sensor and triggers **real-time alerts** when abnormal conditions are detected.

Key capabilities include:
- 🚨 Immediate buzzer alert  
- 📧 Email notification via SMTP  
- 📟 Live status display on LCD  
- 🧠 Intelligent baseline calibration  

This solution demonstrates a **reliable, real-world industrial safety system** using IoT technologies.

---

## 🧠 System Architecture


Gas Sensor (MQ2)
↓
ESP8266
↓
┌───────────────┬───────────────┐
↓ ↓ ↓
LCD Display Buzzer Alert SMTP Email


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| ESP8266 (NodeMCU / D1 R2) | 1 |
| MQ-2 Gas Sensor | 1 |
| 16x2 LCD (I2C) | 1 |
| Buzzer | 1 |
| Power Supply | 1 |
| Jumper Wires | As required |

---

## 🔌 Circuit Connections

| Component | ESP8266 Pin |
|----------|------------|
| MQ-2 Analog Output | A0 |
| Buzzer | D5 |
| LCD SDA | D2 |
| LCD SCL | D1 |
| VCC | 5V |
| GND | GND |

---

## ⚙️ Working Principle

1. System powers ON and connects to WiFi  
2. Gas sensor undergoes **baseline calibration**  
3. Continuous monitoring of gas levels  
4. If gas exceeds threshold:
   - 🚨 Buzzer is triggered  
   - 📧 Email alert is sent  
   - 📟 LCD displays alert status  

5. System includes **cooldown logic** to prevent repeated alerts  

---

## 🧠 Detection Logic


Baseline = Average sensor reading
Threshold = Baseline + Offset

IF Gas > Threshold:
→ Trigger Alert
ELSE:
→ System Safe


---

## 💻 Software Implementation

- Platform: Arduino IDE  
- Language: Embedded C++  
- Libraries:
  - ESP8266WiFi  
  - ESP Mail Client  
  - LiquidCrystal I2C  

---

## 🚀 Key Features

- 🔥 Real-time gas leak detection  
- 🧠 Adaptive baseline calibration  
- 📧 Automated email alerts (SMTP)  
- 🚨 Audible buzzer warning  
- 📟 LCD live monitoring  
- ⏱️ Alert cooldown protection  
- ⚡ Noise-filtered sensor readings  

---

## 📷 Output

### LCD Display
- Gas value (live)
- System status (SAFE / ALERT)

### Alert Behavior
- Buzzer activates instantly  
- Email sent to configured recipient  

(Add project images / demo video here)

---

## 📧 Email Alert Example


Subject: URGENT: Gas Leakage Detected

ALERT!

Gas Leakage Detected
Gas Value: XXXX
Baseline: XXXX

Immediate Action Required


---

## 🎯 Applications

- Industrial safety systems  
- Chemical plants  
- Manufacturing units  
- Smart factories  
- Gas leakage monitoring systems  
- Fire hazard detection  

---

## ⚠️ Safety Considerations

- Use proper power supply for sensors  
- Ensure relay isolation if extended to high-power systems  
- Place sensor in ventilated area  
- Calibrate sensor before operation  

---

## 🔮 Future Enhancements

- 🌐 IoT dashboard (Firebase / MQTT)  
- 📱 Mobile push notifications  
- 🔥 Multi-sensor integration (Temperature + Flame)  
- 📊 Data logging & analytics  
- 🚨 Emergency shutdown system  

---

## 🧩 Integration Potential

This system can integrate with:
- Industrial automation systems  
- SCADA platforms  
- Smart factory monitoring  
- IoT dashboards  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Project Highlights

✔ Industrial-grade safety system  
✔ IoT + SMTP integration  
✔ Real-time alerting mechanism  
✔ Embedded system reliability design  
