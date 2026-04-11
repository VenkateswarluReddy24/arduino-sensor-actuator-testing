# 🤖 Autonomous Obstacle Avoidance Robot (Ultrasonic + Servo)

## 📌 Overview
This project implements an **autonomous mobile robot** capable of detecting and avoiding obstacles using an ultrasonic sensor and servo-based scanning.

The system intelligently analyzes surroundings and decides the optimal direction to navigate in real time.

---

## 🧠 System Architecture


Ultrasonic Sensor → Arduino → Decision Logic → Motor Driver → Robot Movement
↓
Servo Scanning


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno / Nano | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| Servo Motor (SG90) | 1 |
| L298N Motor Driver | 1 |
| DC Motors | 2 |
| Robot Chassis | 1 |

---

## 🔌 Connections

### Ultrasonic
| Pin | Arduino |
|-----|--------|
| TRIG | D3 |
| ECHO | D2 |

### Servo
| Pin | Arduino |
|-----|--------|
| Signal | D11 |

### Motor Driver
| Pin | Arduino |
|-----|--------|
| ENA | D5 |
| ENB | D6 |
| IN1 | D7 |
| IN2 | D8 |
| IN3 | D9 |
| IN4 | D12 |

---

## ⚙️ Working Principle

1. Robot moves forward continuously  
2. Measures distance using ultrasonic sensor  
3. If obstacle detected:
   - Stops movement  
   - Scans left and right using servo  
   - Compares distances  
   - Chooses best path  
4. Executes turn and continues  

---

## 🧠 Decision Logic

- Distance > threshold → Move forward  
- Distance ≤ threshold → Scan environment  
- Choose direction with maximum clearance  

---

## 🚀 Features

- Real-time obstacle detection  
- Servo-based environmental scanning  
- Intelligent path selection  
- Smooth motor control  
- Autonomous navigation  

---

## 📷 Output

- Robot avoids obstacles automatically  
- Smooth directional movement  
- Real-time decision making  

---

## 🎯 Applications

- Autonomous robotics  
- Smart navigation systems  
- Industrial AGV prototypes  
- Surveillance robots  

---

## ⚠️ Notes

- Proper calibration required  
- Stable power supply recommended  
- Sensor accuracy depends on environment  

---

## 🔮 Future Enhancements

- AI-based path planning  
- SLAM integration  
- IoT monitoring  
- Obstacle classification  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Autonomous robotics system  
✔ Sensor fusion + control logic  
✔ Real-time decision making  
✔ Industry-relevant project
