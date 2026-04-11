/*
  🔊 Sound Event Detection System (Interrupt + Debounce)

  Features:
  - Real-time sound detection (active LOW sensor)
  - Non-blocking LED indication
  - Noise filtering (debounce logic)
  - Event-based architecture
  - Serial debug output

  Author: Venkateswarlu Reddy
*/

// ---------------- PINS ----------------
#define SOUND_PIN 2
#define LED_PIN   13

// ---------------- PARAMETERS ----------------
#define LED_ON_TIME 1000      // ms
#define DEBOUNCE_TIME 200     // ms

// ---------------- VARIABLES ----------------
unsigned long lastTriggerTime = 0;
unsigned long ledTimer = 0;

bool ledState = false;

// ================= SETUP =================
void setup()
{
  pinMode(SOUND_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);

  Serial.println("Sound Detection System Ready");
}

// ================= LOOP =================
void loop()
{
  detectSound();
  handleLED();
}

// ================= SOUND DETECTION =================
void detectSound()
{
  int soundState = digitalRead(SOUND_PIN);

  // ACTIVE LOW trigger
  if (soundState == LOW)
  {
    unsigned long currentTime = millis();

    // Debounce protection
    if (currentTime - lastTriggerTime > DEBOUNCE_TIME)
    {
      lastTriggerTime = currentTime;

      Serial.println("[EVENT] Sound Detected");

      ledState = true;
      ledTimer = currentTime;
    }
  }
}

// ================= LED CONTROL =================
void handleLED()
{
  if (ledState)
  {
    digitalWrite(LED_PIN, HIGH);

    if (millis() - ledTimer > LED_ON_TIME)
    {
      digitalWrite(LED_PIN, LOW);
      ledState = false;
    }
  }
}
