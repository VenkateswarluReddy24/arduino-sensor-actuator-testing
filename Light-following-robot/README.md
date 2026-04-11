# 🤖 PID-Based Light Following Robot (Embedded Control System)

## 📌 Overview
This project implements a **PID-based Light Following Robot** using digital light sensors (LM393) and an Arduino-compatible microcontroller.

The robot detects light intensity and dynamically adjusts its motion using a **Proportional–Derivative (PD) control algorithm**, enabling smooth and stable navigation toward a light source.

This project demonstrates **control systems engineering, sensor interfacing, and real-time motor control**, making it a strong foundation for autonomous robotics.

---

## 🧠 System Architecture


Light Source
↓
LM393 Sensors (Left & Right)
↓
Microcontroller (PID Control)
↓
Motor Driver (L298N / L293D)
↓
DC Motors → Robot Movement


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno / Nano | 1 |
| LM393 Light Sensor Modules | 2 |
| Motor Driver (L298N / L293D) | 1 |
| DC Motors | 2 |
| Robot Chassis | 1 |
| Power Supply (Battery) | 1 |
| Jumper Wires | As required |

---

## 🔌 Circuit Connections

### 🔹 Sensors
| Sensor | Arduino Pin |
|-------|------------|
| Left Sensor (D0) | D2 |
| Right Sensor (D0) | D12 |

### 🔹 Motor Driver
| Motor Driver | Arduino Pin |
|-------------|------------|
| ENA | D6 |
| ENB | D5 |
| IN1 | D10 |
| IN2 | D9 |
| IN3 | D8 |
| IN4 | D7 |

---

## ⚙️ Working Principle

The robot uses two digital light sensors:

- **LOW → Light detected**
- **HIGH → Dark**

Based on sensor input:

| Left Sensor | Right Sensor | Behavior |
|------------|-------------|----------|
| Light | Light | Move Forward |
| Light | Dark | Turn Left |
| Dark | Light | Turn Right |
| Dark | Dark | Stop |

---

## 🧠 Control Algorithm (PID-Based)

The system uses a simplified **PD controller**:


Error = Sensor Difference

Correction = (Kp × Error) + (Kd × Derivative)

Left Speed = Base Speed + Correction
Right Speed = Base Speed - Correction


### Control Behavior:
- **Proportional (Kp)** → Immediate correction  
- **Derivative (Kd)** → Smooth stabilization  
- **Integral (Ki)** → Disabled (not required for this system)  

---

## 💻 Software Implementation

- Platform: Arduino IDE  
- Language: Embedded C/C++  
- Communication: Serial Monitor (debugging)  

---

## 🚀 Key Features

- 🤖 Autonomous light tracking  
- 🎯 PID-based motion correction  
- ⚡ Real-time sensor processing  
- 🔄 Smooth directional control  
- 🧠 Control systems implementation  
- 🛑 Safe stop when no light detected  

---

## 📷 Output

### Behavior:
- Robot follows light source smoothly  
- Adjusts direction dynamically  
- Stops when light is not detected  

(Add robot images / demo video here)

---

## 🎯 Applications

- Autonomous robotics  
- Light-guided navigation systems  
- Educational robotics platforms  
- Control systems learning  
- Industrial AGV prototypes  

---

## ⚠️ System Considerations

- Sensor sensitivity must be calibrated  
- Ambient light conditions affect performance  
- Proper motor power supply required  

---

## 🔮 Future Enhancements

- 🔆 Analog light sensing for precision  
- 🎯 Full PID (including integral term)  
- 🤖 Obstacle avoidance integration  
- 📡 IoT monitoring dashboard  
- 🧠 AI-based light tracking  

---

## 🧩 Integration Potential

This system can be extended into:

- Line following robots  
- Autonomous navigation systems  
- Smart robotic vehicles  
- Industrial automation robots  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Project Highlights

✔ Control systems (PID) implementation  
✔ Real-time embedded processing  
✔ Robotics + sensor fusion  
✔ Industry-relevant algorithm design  
