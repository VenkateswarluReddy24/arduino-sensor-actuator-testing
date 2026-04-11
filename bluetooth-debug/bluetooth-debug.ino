/*
  🔧 Bluetooth Communication Debug Tool (HC-05 / HC-06)

  Features:
  - Real-time serial monitoring
  - Bidirectional communication test
  - Command echo verification
  - Debug-friendly output formatting

  Author: Venkateswarlu Reddy
*/

#define BAUD_RATE 9600

char receivedData;

void setup() {
  Serial.begin(BAUD_RATE);
  delay(1000);

  Serial.println("=================================");
  Serial.println("  BLUETOOTH DEBUG INTERFACE READY ");
  Serial.println("=================================");
  Serial.println("Send characters from mobile app...");
  Serial.println();
}

void loop() {

  // Check incoming Bluetooth data
  if (Serial.available() > 0) {

    receivedData = Serial.read();

    // Display received data
    Serial.print("[RX] Received: ");
    Serial.println(receivedData);

    // Echo back to sender
    Serial.print("[TX] Echo: ");
    Serial.println(receivedData);

    // Optional: ASCII value (useful for debugging)
    Serial.print("[INFO] ASCII: ");
    Serial.println((int)receivedData);

    Serial.println("------------------------------");
  }
}
