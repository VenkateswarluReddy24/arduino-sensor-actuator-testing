# 🎙️ ESP32 Voice Home Automation — SinricPro + Google Home

> A portfolio-ready IoT demonstration that turns a single LED into a cloud-connected smart-home actuator using **ESP32 + SinricPro + Google Home**.

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue?style=flat-square)](https://www.espressif.com/en/products/socs/esp32)
[![Framework](https://img.shields.io/badge/Framework-Arduino-orange?style=flat-square)](https://www.arduino.cc/)
[![IoT](https://img.shields.io/badge/IoT-SinricPro-6f42c1?style=flat-square)](https://sinric.pro/)
[![Voice](https://img.shields.io/badge/Voice-Google%20Home-red?style=flat-square)](https://www.google.com/home/)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)](LICENSE)

## 🚀 Project Snapshot

Speak:

> **“Hey Google, turn on Demo Light.”**

Google Assistant interprets the command, Google Home routes the smart-home request through SinricPro, the ESP32 receives the power-state callback over Wi-Fi, and GPIO 2 drives the LED.

This intentionally small build demonstrates a real IoT control chain without mains electricity:

**Natural language → cloud smart-home service → Wi-Fi device → embedded callback → physical actuator**

## 🧠 System Architecture

```text
                YOUR VOICE
                    │
                    ▼
             Google Assistant
                    │
                    ▼
               Google Home
                    │
                    ▼
              SinricPro Cloud
                    │
                 Internet
                    │
                    ▼
               ESP32 Wi-Fi
                    │
                    ▼
                  GPIO 2
                    │
                    ▼
                   LED
```

| Layer | Responsibility |
|---|---|
| Google Assistant | Speech recognition + natural-language command |
| Google Home | Smart-home device integration |
| SinricPro | Cloud IoT bridge + device control |
| ESP32 | Wi-Fi client + embedded device logic |
| GPIO 2 | Digital actuator output |
| LED | Low-voltage physical load |

## ✨ Engineering Features

- 🎙️ Natural voice ON/OFF control
- ☁️ SinricPro cloud integration
- 🏠 Google Home integration
- 📱 SinricPro app as a presentation backup
- 💡 Single LED actuator on GPIO 2
- 🔄 Wi-Fi auto-reconnect handling
- 🛡️ Safe startup with LED OFF
- 📟 Serial diagnostics for network/cloud/device state
- 🧠 Small, understandable embedded firmware
- 🔐 Local credentials separated from source code
- 📦 No unnecessary web server/WebSocket layer

## 🛠️ Hardware

| Component | Qty | Purpose |
|---|---:|---|
| ESP32 Dev Module | 1 | IoT controller |
| LED | 1 | Demonstration actuator |
| 220Ω resistor | 1 | LED current limiting |
| Jumper wires | 2–3 | Connections |
| USB cable | 1 | Programming + power |

### Wiring

```text
ESP32 GPIO 2
     │
     ▼
   220Ω resistor
     │
     ▼
 LED anode (+)
 LED cathode (-)
     │
     ▼
    GND
```

Some ESP32 boards expose an onboard LED on GPIO 2, allowing a quick hardware test without the external LED.

## 💻 Software Stack

- Arduino IDE
- ESP32 board package by Espressif Systems
- SinricPro Arduino library
- SinricPro account
- Google Home app
- Internet-connected Wi-Fi

## 📁 Project Structure

```text
ESP32_Voice_Home_Automation_SinricPro/
├── ESP32_Voice_Home_Automation_SinricPro.ino
├── config.example.h
├── .gitignore
├── LICENSE
└── README.md
```

## ⚙️ Arduino IDE Setup

1. Install **Arduino IDE**.
2. Install **ESP32 by Espressif Systems** through Boards Manager.
3. Select **ESP32 Dev Module**.
4. Open Library Manager and install **SinricPro**.
5. Copy the credential template:

```text
config.example.h → config.h
```

6. Edit `config.h` on your computer and enter your Wi-Fi/SinricPro credentials.
7. Upload `ESP32_Voice_Home_Automation_SinricPro.ino`.

`config.h` is deliberately ignored by Git so credentials are not published.

## 🔐 Credentials & Security

The tracked repository contains only placeholders in `config.example.h`.

Your local `config.h` must contain:

```cpp
#define WIFI_SSID   "YOUR_WIFI_NAME"
#define WIFI_PASS   "YOUR_WIFI_PASSWORD"
#define APP_KEY     "YOUR_SINRICPRO_APP_KEY"
#define APP_SECRET  "YOUR_SINRICPRO_APP_SECRET"
#define SWITCH_ID   "YOUR_SINRICPRO_DEVICE_ID"
```

**Never commit real Wi-Fi passwords, SinricPro App Keys, App Secrets, or private device identifiers to a public repository.**

## ☁️ SinricPro Device Setup

1. Create/sign in to your SinricPro account.
2. Create one **Switch** device.
3. Use a simple device name such as **Demo Light**.
4. Copy the Device ID.
5. Copy your App Key and App Secret.
6. Place those values only in local `config.h`.

For this one-device classroom demo, the free tier is sufficient.

## 🏠 Google Home Setup

In the Google Home app:

```text
Add
→ Set up device
→ Works with Google Home
→ Search for Sinric Pro
→ Link your SinricPro account
→ Discover devices
```

Assign the device to a room and keep the device name short.

Recommended name:

> **Demo Light**

Voice tests:

> “Hey Google, turn on Demo Light.”

> “Hey Google, turn off Demo Light.”

## 🔌 Firmware Logic

The main firmware performs five jobs:

1. Initialize GPIO 2 safely with the LED OFF.
2. Connect the ESP32 to a normal Wi-Fi network.
3. Authenticate with SinricPro.
4. Receive the Power State callback.
5. Drive GPIO 2 HIGH/LOW and report the result through Serial Monitor.

The central callback is:

```cpp
bool onPowerState(const String &deviceId, bool &state)
```

`state == true` turns the LED ON; `state == false` turns it OFF.

## 🧪 Expected Serial Monitor

Use **115200 baud**.

Startup should look similar to:

```text
========================================
      ESP32 VOICE HOME AUTOMATION
========================================
LED STATE: OFF
Hardware initialized.
GPIO 2 LED = OFF

WIFI CONNECTION
Connecting to Wi-Fi.......
Wi-Fi connected.
IP address: 192.168.x.x

SINRICPRO SETUP
SinricPro client started.

Connected to SinricPro.
Cloud connection: ONLINE
```

After a command:

```text
--------------------------------
Device ID: <device-id>
Received command: TURN ON
LED STATE: ON
Recognized action: LED ON
Free heap: <value>
--------------------------------
```

## 🎬 Presentation Flow

### 1. Show the hardware

Point out:

- ESP32 controller
- GPIO 2
- 220Ω resistor
- LED actuator

### 2. Demonstrate voice control

Say:

> **“Hey Google, turn on Demo Light.”**

LED → **ON**

Then:

> **“Hey Google, turn off Demo Light.”**

LED → **OFF**

### 3. Show the cloud-to-device path

Explain:

```text
Voice
 ↓
Google Assistant
 ↓
Google Home
 ↓
SinricPro
 ↓
Wi-Fi
 ↓
ESP32
 ↓
GPIO 2
 ↓
LED
```

### 4. Demonstrate the backup

Open the SinricPro app and toggle **Demo Light** directly.

This gives you a second control path if voice recognition is unavailable during the presentation.

## ⚠️ Important Architecture Limitation

This version intentionally **does not use the ESP32 as an isolated Wi-Fi Access Point**.

SinricPro and Google Home require the ESP32 to reach the internet.

The control path is:

```text
ESP32 → Internet → SinricPro → Google Home
```

The physical actuator remains directly controlled by the ESP32 after the command reaches the device.

## 🔍 Troubleshooting

### ESP32 does not connect to Wi-Fi

Check `WIFI_SSID` and `WIFI_PASS` in local `config.h`. Confirm that the network has internet access.

### SinricPro does not connect

Verify:

```text
APP_KEY
APP_SECRET
SWITCH_ID
```

All three must belong to the correct SinricPro account/device.

### Google Home cannot find the device

Relink SinricPro under:

```text
Google Home
→ Add
→ Set up device
→ Works with Google Home
```

Then run discovery again.

### Serial says LED ON but the LED stays dark

Check:

```text
GPIO 2 → 220Ω → LED anode
LED cathode → GND
```

### Voice command is unreliable

Use a simple device name such as **Demo Light** and short commands:

> “Turn on Demo Light.”

> “Turn off Demo Light.”

## 🛡️ Safety

This repository uses a single LED and is intended for low-voltage STEM/IoT demonstration.

**Do not connect mains AC directly to ESP32 GPIO.**

For future home-automation expansion, use an appropriately rated isolated relay module and follow electrical safety practices.

## 📌 Portfolio Value

Although the actuator is only one LED, the project demonstrates several industry-relevant layers:

- Embedded C/C++ firmware
- ESP32 Wi-Fi networking
- Cloud IoT integration
- Smart-home device abstraction
- Event-driven callbacks
- State synchronization
- Fault recovery through Wi-Fi reconnect
- Secure handling of development credentials

## 👨‍💻 Author

**Venkateswarlu Reddy Bakka**  
Robotics • Embedded Systems • IoT • STEM Education

## 📄 License

MIT License — see [LICENSE](LICENSE).
