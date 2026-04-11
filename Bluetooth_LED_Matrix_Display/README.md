# 📟 Bluetooth LED Matrix Display System (MAX7219)

## 📌 Overview
This project implements a **Bluetooth-controlled LED matrix display system** using MAX7219 modules.

The system receives text wirelessly and displays it as **scrolling messages** across multiple LED matrices.

---

## 🧠 System Architecture


Mobile → Bluetooth (HC-05) → Arduino → LED Matrix (MAX7219)


---

## 🛠️ Hardware Components

| Component | Quantity |
|----------|---------|
| Arduino Uno / Nano | 1 |
| MAX7219 LED Matrix | 4 |
| HC-05 Bluetooth Module | 1 |
| Jumper Wires | As required |

---

## 🔌 Connections

### MAX7219
| Pin | Arduino |
|-----|--------|
| DIN | D11 |
| CLK | D13 |
| CS  | D10 |

### Bluetooth
| HC-05 | Arduino |
|------|--------|
| TX | D9 |
| RX | D8 |

---

## ⚙️ Working Principle

- User sends message via Bluetooth  
- System splits message into words  
- Each matrix displays one word  
- Text scrolls continuously  

---

## 🚀 Features

- 📡 Wireless text display  
- 📟 Multi-matrix scrolling  
- 🎨 Border animation effect  
- ⚡ Smooth non-blocking execution  

---

## 📷 Output

- Real-time scrolling text  
- Multi-panel synchronized display  

---

## 🎯 Applications

- Smart notice boards  
- Information display systems  
- Industrial dashboards  
- Event display panels  

---

## ⚠️ Notes

- Keep proper power supply for matrices  
- Ensure Bluetooth baud rate matches  
- Avoid long blocking strings  

---

## 🔮 Future Enhancements

- Mobile app interface  
- Emoji / symbol support  
- WiFi-based display  
- Dynamic animations  

---

## 👨‍💻 Author
Venkateswarlu Reddy Bakka

---

## ⭐ Highlights

✔ Embedded display systems  
✔ Wireless communication  
✔ Multi-device synchronization  
✔ Real-time rendering  
