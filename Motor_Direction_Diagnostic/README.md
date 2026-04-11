# 🔧 Motor Direction Diagnostic Tool (L298N + Arduino)

## 📌 Overview
This project is a **motor debugging and validation tool** designed to test DC motor direction and wiring using an L298N motor driver.

It systematically verifies:
- Forward motion  
- Reverse motion  
- Left turn  
- Right turn  

This tool is essential during the development of **robotic systems and mobile platforms**.

---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno / Nano | 1 |
| L298N Motor Driver | 1 |
| DC Motors | 2 |
| Power Supply | 1 |

---

## 🔌 Circuit Connections

| Motor Driver | Arduino |
|-------------|--------|
| IN1 | D7 |
| IN2 | D8 |
| IN3 | D9 |
| IN4 | D10 |
| ENA | D6 |
| ENB | D5 |

---

## ⚙️ Working Principle

The system runs a sequence of motor tests:

1. Forward → Both wheels forward  
2. Reverse → Both wheels backward  
3. Left → Differential turning  
4. Right → Differential turning  

Each test is followed by a stop phase.

---

## 🚀 Features

- 🔧 Motor wiring validation  
- 🎯 Direction testing  
- 🧠 Structured test sequence  
- 📟 Serial debug output  

---

## 📷 Output

### Serial Monitor:

[TEST] FORWARD
[TEST] STOP
[TEST] REVERSE
[TEST] STOP
...


---

## 🎯 Applications

- Robotics development  
- Motor driver testing  
- Hardware debugging  
- Embedded system validation  

---

## ⚠️ Notes

- Ensure proper motor power supply  
- Verify connections before testing  
- Use safe speed during testing  

---

## 🔮 Future Enhancements

- Add encoder feedback  
- PWM speed testing  
- Automated calibration system  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Hardware debugging skills  
✔ Robotics system validation  
✔ Motor control understanding
