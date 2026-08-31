# 🤖 ESP8266 Wi-Fi Robot

> A locally controlled ESP8266 mobile robot demonstrating wireless communication, embedded motor control, PWM speed control, WebSocket communication, and communication-failsafe design.

![ESP8266 Wi-Fi Robot](media/robot.jpg)

---

## 📌 Project Overview

This project is a two-wheel differential-drive Wi-Fi robot built around the ESP8266 microcontroller and L298N dual H-bridge motor driver.

The robot was originally developed using an HTTP-based control architecture with MIT App Inventor and a compact NodeMCU board.

The system was later upgraded to a WebSocket-based control architecture using a larger LoLin NodeMCU ESP-12E board and the ESP Wi-fi Car Controller application.

The project focuses on reliable embedded control rather than simply adding unnecessary features.

### Engineering priorities

1. Reliability
2. Safety
3. Educational value
4. Demonstration quality

---

# 🚀 Current Version

## F1 — WebSocket + LoLin ESP-12E

The current validated version uses:

- LoLin NodeMCU ESP-12E
- ESP8266
- L298N motor driver
- DC geared motors
- ESP Wi-fi Car Controller Android application
- WebSocket communication
- Local Wi-Fi SoftAP
- PWM speed control
- Communication watchdog
- Automatic stop on communication failure

### Current status

**F1: STABLE / TESTED**

---

# ✨ Features

## Wireless Control

The ESP8266 creates its own Wi-Fi access point.

```text
Phone
  ↓
Wi-Fi
  ↓
ESP8266 SoftAP
  ↓
WebSocket
  ↓
Command Processor
  ↓
L298N
  ↓
DC Motors
