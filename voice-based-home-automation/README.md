# 🏠 Voice Controlled Smart Home Automation (Google Home + ESP8266 + Sinric Pro)

## 📌 Overview
This project implements a **voice-controlled home automation system** using **Google Assistant, ESP8266, and Sinric Pro cloud platform**.

Users can control electrical appliances using natural voice commands such as:
- “Turn on the light”
- “Turn off the fan”

The system enables **hands-free automation**, demonstrating real-world IoT integration with voice ecosystems.

---

## 🧠 System Architecture


Google Assistant (Voice)
↓
Sinric Pro Cloud
↓
ESP8266
↓
Relay Module
↓
Electrical Devices


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| ESP8266 (NodeMCU) | 1 |
| Relay Module (2/4 Channel) | 1 |
| Electrical Loads (Light/Fan) | As needed |
| Jumper Wires | As required |
| Power Supply | 1 |

---

## 🔌 Circuit Connections

| Device | ESP8266 Pin |
|-------|------------|
| Relay 1 (Light) | D1 |
| Relay 2 (Fan) | D2 |
| VCC | 5V |
| GND | GND |

⚠️ Note: Relays are typically **Active LOW**

---

## ⚙️ Working Principle

1. User gives voice command via Google Assistant  
2. Command is sent to **Sinric Pro Cloud**  
3. ESP8266 receives command via WebSocket  
4. Corresponding relay is triggered  
5. Device turns ON/OFF  

---

## 🗣️ Supported Voice Commands

- “Turn ON Light”
- “Turn OFF Light”
- “Turn ON Fan”
- “Turn OFF Fan”

---

## 💻 Software Implementation

- Platform: Arduino IDE  
- Language: Embedded C++  
- Libraries:
  - ESP8266WiFi  
  - SinricPro  
  - WebSockets  

---

## 🚀 Key Features

- 🗣️ Voice control using Google Assistant  
- ☁️ Real-time cloud communication  
- ⚡ Instant device response  
- 📱 No custom app required  
- 🔌 Multi-device control  
- 🌐 Remote access from anywhere  

---

## 📷 Output

### System Behavior:
- Devices respond instantly to voice commands  
- No manual switch interaction required  

(Add images / demo video here)

---

## 🎯 Applications

- Smart home automation  
- Assistive technology (hands-free control)  
- IoT-based control systems  
- Voice-enabled industrial prototypes  

---

## ⚠️ Safety Considerations

- Use proper relay modules with isolation  
- Ensure safe handling of AC loads  
- Avoid overloading circuits  

---

## 🔮 Future Enhancements

- 📱 Mobile dashboard integration  
- 🔒 Authentication & user roles  
- 🌐 MQTT-based architecture  
- ⚡ Energy monitoring system  
- 🤖 AI-based automation  

---

## 🧩 Integration Potential

Can be integrated with:
- Smart home ecosystems  
- IoT dashboards  
- Industrial automation systems  
- Voice-controlled robotics  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka
