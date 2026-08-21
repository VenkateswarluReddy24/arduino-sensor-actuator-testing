# IR Remote Controlled Robot Car

> Arduino-based differential-drive mobile robot controlled through an infrared remote, featuring configurable speed levels, directional movement, emergency stop and one-shot 360° rotation.

## Overview

This project implements an IR remote controlled mobile robot using an Arduino, IR receiver and motor driver.

The firmware decodes IR remote commands and translates them into motor direction and speed control commands.

## Features

- IR remote control
- Forward movement
- Backward movement
- Left and right turning
- 9 selectable speed levels
- Software PWM motor control
- Emergency stop
- Stop command
- 360° rotation using the OK button
- IR repeat-frame filtering
- Serial command diagnostics

## Control Mapping

| Remote Button | Function |
|---|---|
| 1–9 | Speed level |
| UP | Forward |
| DOWN | Backward |
| LEFT | Left |
| RIGHT | Right |
| 0 | Stop |
| * | Emergency stop |
| OK | 360° rotation |
| # | Reset speed to level 5 |

## Hardware

| Component | Purpose |
|---|---|
| Arduino | Main controller |
| IR receiver | Remote command input |
| Motor driver | Motor direction/control |
| DC gear motors | Robot movement |
| LED | Movement/status indication |

## Pin Configuration

| Function | Arduino Pin |
|---|---:|
| IR Receiver | D2 |
| ENA | D3 |
| Motor IN1 | D4 |
| Motor IN2 | D5 |
| Motor IN3 | D6 |
| Motor IN4 | D7 |
| ENB | D9 |
| Status LED | D13 |

## Firmware Architecture

```text
IR Remote
    ↓
IR Receiver
    ↓
IR Command Decoder
    ↓
Command Processing
    ↓
Speed / Movement Logic
    ↓
Motor Driver
    ↓
DC Motors
