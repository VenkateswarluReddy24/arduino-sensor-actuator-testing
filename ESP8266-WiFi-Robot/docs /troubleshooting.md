# Troubleshooting

## Robot moves continuously

Check:

1. Controller application is sending movement commands.
2. Stop command is being received.
3. Watchdog is enabled.
4. WebSocket connection status.

---

## Robot does not move

Check:

1. Wi-Fi connection.
2. WebSocket IP address.
3. WebSocket port.
4. L298N motor power.
5. Common ground.
6. Motor wiring.

---

## Robot moves in the wrong direction

Check:

- Motor polarity
- IN1/IN2 wiring
- IN3/IN4 wiring

Motor polarity can be corrected by reversing the relevant motor wires or changing the corresponding direction logic.

---

## Robot stops unexpectedly

Check:

- Wi-Fi signal
- Controller application
- Watchdog timeout
- Battery voltage
- L298N power supply
