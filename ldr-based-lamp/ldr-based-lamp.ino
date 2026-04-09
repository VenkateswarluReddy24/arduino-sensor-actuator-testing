/*
 * Project: Automatic Night Lamp using LDR (LM393)
 * Author: [Your Name]
 * Board: Arduino / NodeMCU (D1 R2)
 * Description:
 * Turns ON LED in darkness and OFF in light based on LDR sensor input.
 */

// ---------------- Pin Definitions ----------------
#define LDR_PIN 7      // Digital output from LM393 module
#define LED_PIN 8      // LED connected to pin 8

// ---------------- Variables ----------------
int ldrState = 0;

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Automatic Night Lamp Initialized");
}

void loop() {

  // Read LDR digital output
  ldrState = digitalRead(LDR_PIN);

  /*
   * LM393 Logic:
   * HIGH  -> Dark
   * LOW   -> Light
   */

  if (ldrState == HIGH) {
    digitalWrite(LED_PIN, HIGH);   // Turn ON LED (Night)
    Serial.println("Dark detected -> LED ON");
  } else {
    digitalWrite(LED_PIN, LOW);    // Turn OFF LED (Day)
    Serial.println("Light detected -> LED OFF");
  }

  delay(200); // Stability delay
}
