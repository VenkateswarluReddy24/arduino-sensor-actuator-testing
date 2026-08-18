# 🎙️ ESP32 Voice Home Automation — SinricPro + Google Home

> A compact smart-home demonstration using an **ESP32 + one LED**, controlled by natural voice through **Google Home** and **SinricPro**.

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue?style=flat-square)](https://www.espressif.com/en/products/socs/esp32)
[![Framework](https://img.shields.io/badge/Framework-Arduino-orange?style=flat-square)](https://www.arduino.cc/)
[![IoT](https://img.shields.io/badge/IoT-SinricPro-6f42c1?style=flat-square)](https://sinric.pro/)
[![Voice](https://img.shields.io/badge/Voice-Google%20Home-red?style=flat-square)](https://www.google.com/home/)

## 🚀 Project Overview

This project turns a single LED into a simple cloud-connected smart-home device.

Speak a command such as:

> **“Hey Google, turn on Demo Light.”**

Google Home sends the smart-home command through SinricPro, the ESP32 receives the command over Wi-Fi, and GPIO 2 drives the LED.

The design intentionally uses a **single low-voltage LED actuator** so it is easy to demonstrate in a classroom, STEM lab, science fair, or IoT presentation without working with mains electricity.

## 🧠 Architecture

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

### What each layer does

| Layer | Responsibility |
|---|---|
| Google Assistant | Speech recognition and natural-language smart-home command |
| Google Home | Smart-home device integration |
| SinricPro | Cloud IoT bridge between assistant/app and ESP32 |
| ESP32 | Wi-Fi connectivity, command callback, device logic |
| GPIO 2 | Digital actuator output |
| LED | Physical demonstration load |

## ✨ Features

- 🎙️ Natural voice ON/OFF control
- ☁️ SinricPro IoT integration
- 🏠 Google Home integration
- 📱 SinricPro app backup control
- 💡 Single LED actuator
- 🔌 GPIO 2 output
- 🔄 Wi-Fi auto-reconnect handling
- 🧪 Safe low-voltage classroom demonstration
- 📟 Serial diagnostics for Wi-Fi, cloud state, commands, LED state, and free heap
- 🧩 Minimal firmware with no unnecessary web server or WebSocket layer

## 🛠️ Hardware

| Component | Quantity |
|---|---:|
| ESP32 Dev Module | 1 |
| LED | 1 |
| 220Ω resistor | 1 |
| Jumper wires | 2–3 |
| USB cable | 1 |

### Wiring

```text
ESP32 GPIO 2
     │
     ▼
   220Ω
 resistor
     │
     ▼
 LED Anode (+)
 LED Cathode (-)
     │
     ▼
    GND
```

Some ESP32 Dev Modules also provide an onboard LED on GPIO 2, so the external LED can be omitted for a quick test when supported by the board.

## 🧰 Software Requirements

- Arduino IDE
- ESP32 board package for Arduino IDE
- SinricPro Arduino library
- SinricPro account
- Google Home app
- Internet-connected Wi-Fi

## 📦 Arduino IDE Setup

1. Install the **ESP32 by Espressif Systems** board package.
2. Select **ESP32 Dev Module**.
3. Open **Library Manager** and install **SinricPro**.
4. Open `ESP32_Voice_Home_Automation_SinricPro.ino`.

## 🔐 Credentials

Open the sketch and replace only these placeholders:

```cpp
#define WIFI_SSID     "YOUR_WIFI_NAME"
#define WIFI_PASS     "YOUR_WIFI_PASSWORD"
#define APP_KEY       "YOUR_APP_KEY"
#define APP_SECRET    "YOUR_APP_SECRET"
#define SWITCH_ID     "YOUR_DEVICE_ID"
```

### Security rule

**Do not commit real Wi-Fi passwords, SinricPro App Keys, App Secrets, or Device IDs to a public repository.**

The repository intentionally contains placeholders only.

## ☁️ SinricPro Setup

1. Create/sign in to a SinricPro account.
2. Create a new **Switch** device.
3. Use a simple device name such as:
   - `Demo Light`
   - `Smart Light`
4. Copy the generated Device ID.
5. Copy your App Key and App Secret.
6. Put those values into the Arduino sketch locally.

For a one-device classroom demo, the free SinricPro tier is sufficient.

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

Add the discovered device to a room and keep the device name simple.

Recommended:

> **Demo Light**

Then test:

> **“Hey Google, turn on Demo Light.”**

and:

> **“Hey Google, turn off Demo Light.”**

## 🧪 Expected Serial Monitor Flow

At startup:

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

After a voice command:

```text
--------------------------------
Device ID: <device-id>
Received command: TURN ON
LED STATE: ON
Recognized action: LED ON
Free heap: <value>
--------------------------------
```

## 🎬 Presentation Demo Flow

### Demo 1 — Voice control

Say:

> “Hey Google, turn on Demo Light.”

The LED turns ON.

Then say:

> “Hey Google, turn off Demo Light.”

The LED turns OFF.

### Demo 2 — App control backup

Open SinricPro and toggle **Demo Light** directly.

This gives you a reliable backup if voice recognition or the microphone is unavailable during the presentation.

## ⚠️ Important Architecture Note

This version **does not use the ESP32 as an isolated Wi-Fi Access Point**.

That is intentional.

SinricPro and Google Home require the ESP32 to reach the internet. The final communication path is:

```text
ESP32 → Internet → SinricPro → Google Home
```

The LED control itself is still performed locally by the ESP32 on GPIO 2 once the command reaches the device.

## 🔍 Troubleshooting

### ESP32 does not connect to Wi-Fi

Check the `WIFI_SSID` and `WIFI_PASS` values and make sure the network has internet access.

### SinricPro does not connect

Check all three values:

```text
APP_KEY
APP_SECRET
SWITCH_ID
```

They must belong to the correct SinricPro account/device.

### Google Home cannot find the device

Relink SinricPro under:

```text
Google Home
→ Add
→ Set up device
→ Works with Google Home
```

Then run device discovery again.

### Serial says LED ON but the LED stays dark

Check the wiring:

```text
GPIO 2 → 220Ω → LED anode
LED cathode → GND
```

Also test the onboard GPIO 2 LED if your ESP32 board provides one.

### Voice command is unreliable

Use a short device name such as **Demo Light** and commands such as:

> “Turn on Demo Light.”

> “Turn off Demo Light.”

## 🔒 Safety

This project uses a single LED and is intended as a low-voltage STEM demonstration.

Do **not** connect mains AC directly to GPIO 2.

For future home-automation expansion, use an appropriately rated, isolated relay module and follow electrical safety requirements.

## 📁 Project Structure

```text
ESP32_Voice_Home_Automation_SinricPro/
├── ESP32_Voice_Home_Automation_SinricPro.ino
└── README.md
```

## 👨‍💻 Author

**Venkateswarlu Reddy Bakka**

Robotics • Embedded Systems • IoT • STEM Education

---

### ⭐ Why this project matters

This is a small hardware build, but it demonstrates a real IoT control chain:

**Natural language → cloud smart-home service → Wi-Fi device → embedded callback → physical actuator.**
