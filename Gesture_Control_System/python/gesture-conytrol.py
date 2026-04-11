# 🎮 Gesture Controlled Media System

import serial
import time
import pyautogui

arduino = serial.Serial('COM7', 9600, timeout=1)
time.sleep(2)

print("Gesture Control System Started")

last_cmd = ""
last_time = 0

COOLDOWN = 0.6
confirm_cmd = ""
confirm_count = 0
REQUIRED_CONFIRM = 2

while True:
    try:
        line = arduino.readline().decode('utf-8', errors='ignore').strip()

        if line == "" or line.startswith("L:"):
            continue

        print("Received:", line)

        # -------- Confirmation Filter --------
        if line == confirm_cmd:
            confirm_count += 1
        else:
            confirm_cmd = line
            confirm_count = 1

        if confirm_count < REQUIRED_CONFIRM:
            continue

        now = time.time()

        if line == last_cmd and (now - last_time) < COOLDOWN:
            continue

        # -------- ACTION MAPPING --------
        actions = {
            "Play": lambda: pyautogui.press('space'),
            "Forward": lambda: pyautogui.press('right'),
            "Rewind": lambda: pyautogui.press('left'),
            "Vup": lambda: pyautogui.hotkey('ctrl', 'up'),
            "Vdown": lambda: pyautogui.hotkey('ctrl', 'down'),
            "Stop": lambda: pyautogui.press('s')
        }

        if line in actions:
            actions[line]()
            print("Executed:", line)

        last_cmd = line
        last_time = now
        confirm_count = 0

    except Exception as e:
        print("Error:", e)
