# IR Remote Robot Car – STEM Demo

A classroom-friendly Arduino UNO robot car controlled using an IR remote and L298N motor driver. The project is designed for a reliable STEM demonstration using the existing hardware setup.

## Features

- IR remote control using Arduino-IRremote 4.x
- Forward, backward, left and right movement
- Stop and emergency stop controls
- Nine selectable speed levels using numeric keys 1–9
- IR repeat-frame filtering to prevent repeated commands from a held button
- 500 ms movement bursts for controlled classroom demonstrations
- **OK button performs one calibrated 360° spin** for a demonstration highlight
- `#` resets the speed to level 5
- Software PWM is used on the L298N enable pins to avoid using `analogWrite()` on D3 with IRremote on Arduino UNO

## Hardware

| Component | Connection |
|---|---|
| Arduino UNO | Main controller |
| IR Receiver | OUT → D2, VCC → 5V, GND → GND |
| L298N | Motor driver |
| ENA | D3 |
| ENB | D9 |
| IN1 | D4 |
| IN2 | D5 |
| IN3 | D6 |
| IN4 | D7 |
| LED | D13 |
| Left motor | L298N motor output A |
| Right motor | L298N motor output B |

**Power:** Use a suitable separate motor supply for the L298N. Keep the Arduino, IR receiver, and L298N grounds common.

## Remote Control

| Button | IR Command | Function |
|---|---:|---|
| 1 | `0x45` | Speed level 1 |
| 2 | `0x46` | Speed level 2 |
| 3 | `0x47` | Speed level 3 |
| 4 | `0x44` | Speed level 4 |
| 5 | `0x40` | Speed level 5 |
| 6 | `0x43` | Speed level 6 |
| 7 | `0x07` | Speed level 7 |
| 8 | `0x15` | Speed level 8 |
| 9 | `0x09` | Speed level 9 |
| 0 | `0x19` | Stop |
| `*` | `0x16` | Emergency stop |
| `#` | `0x0D` | Reset speed to level 5 |
| Up | `0x18` | Forward |
| Down | `0x52` | Backward |
| Left | `0x08` | Left |
| Right | `0x5A` | Right |
| OK | `0x1C` | One 360° demonstration rotation |

## Demo Behavior

Movement commands run for approximately **500 ms** and then stop automatically. This makes repeated classroom demonstrations easy to control.

The **OK** button performs a single spin using the two motors in opposite directions. The default rotation time is `800 ms`.

Because the robot has no wheel encoders or IMU, the 360° rotation is **time-calibrated, not precision measured**. Exact rotation depends on motor speed, battery voltage, wheel diameter, chassis weight, tyre grip, and floor surface. Adjust `ROTATION_TIME` in `main.ino` for your actual chassis.

## Speed Levels

| Level | PWM value | Use |
|---|---:|---|
| 1 | 60 | Very slow |
| 2 | 80 | Slow |
| 3 | 105 | Slow-medium |
| 4 | 130 | Medium |
| 5 | 155 | Default |
| 6 | 180 | Medium-fast |
| 7 | 205 | Fast |
| 8 | 230 | Very fast |
| 9 | 255 | Maximum |

## Software

- Arduino IDE
- Arduino-IRremote 4.x
- Arduino C++

## How It Works

```text
IR Remote
    ↓
IR Receiver (D2)
    ↓
Arduino UNO
    ↓
Command decoding + speed selection
    ↓
L298N Motor Driver
    ↓
DC Motors
```

The program ignores IR repeat frames so a held button does not repeatedly trigger the same action. Movement and rotation use software PWM on the enable pins to keep the existing pin assignment while avoiding the Arduino UNO Timer2 conflict associated with hardware PWM on D3 and the IRremote receiver.

## Project Structure

```text
IR_Remote_Robot_Car/
├── README.md
└── code/
    └── main.ino
```

## Calibration

For the 360° presentation feature:

1. Set the robot to a repeatable speed, preferably level 5.
2. Press **OK** once.
3. If the robot turns less than 360°, increase `ROTATION_TIME`.
4. If it overshoots, decrease `ROTATION_TIME`.

Example values:

```cpp
const unsigned long ROTATION_TIME = 700;
```

or

```cpp
const unsigned long ROTATION_TIME = 900;
```

## STEM Learning Concepts

This project demonstrates:

- Infrared communication
- Digital input processing
- Embedded programming
- Motor direction control
- H-bridge motor driving
- PWM-based speed control
- Event/repeat handling
- Actuator control
- Time-based motion control
- Practical calibration and experimentation

## Demo Notes

This is a **STEM presentation robot**, not a precision navigation platform. The 360° feature is intended as an engaging demonstration effect and should be calibrated on the actual robot before presentation.
