/*
  ✋ Ultrasonic Gesture Recognition System

  Features:
  - Dual ultrasonic sensor gesture detection
  - Majority filtering (noise reduction)
  - Cooldown + gesture lock system
  - Serial output for PC automation

  Author: Venkateswarlu Reddy
*/

// ---------------- PINS ----------------
#define TRIG_LEFT  6
#define ECHO_LEFT  7
#define TRIG_RIGHT 8
#define ECHO_RIGHT 9

// ---------------- PARAMETERS ----------------
#define COOLDOWN 700
#define HISTORY_SIZE 5

float distL, distR;

unsigned long lastAction = 0;
bool gestureLock = false;

// Gesture history buffer
String history[HISTORY_SIZE];
int histIndex = 0;

// ================= DISTANCE =================
float readDistance(int trig, int echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);

  return duration * 0.0343 / 2.0;
}

// ================= GESTURE =================
String detectGesture(float L, float R)
{
  // LEFT SENSOR
  if(L>=5 && L<=10) return "Stop";
  if(L>=12 && L<=20) return "Vdown";
  if(L>=25 && L<=40) return "Vup";

  // RIGHT SENSOR
  if(R>=5 && R<10) return "Play";
  if(R>=15 && R<=25) return "Forward";
  if(R>=28 && R<=40) return "Rewind";

  return "";
}

// ================= FILTER =================
String getStableGesture()
{
  int maxCount = 0;
  String best = "";

  for(int i=0;i<HISTORY_SIZE;i++)
  {
    int count = 0;

    for(int j=0;j<HISTORY_SIZE;j++)
    {
      if(history[i] == history[j] && history[i] != "")
        count++;
    }

    if(count > maxCount)
    {
      maxCount = count;
      best = history[i];
    }
  }

  return best;
}

// ================= SETUP =================
void setup()
{
  Serial.begin(9600);

  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  Serial.println("Gesture System Ready");
}

// ================= LOOP =================
void loop()
{
  if(millis() - lastAction < COOLDOWN) return;

  distL = readDistance(TRIG_LEFT, ECHO_LEFT);
  delay(30);
  distR = readDistance(TRIG_RIGHT, ECHO_RIGHT);

  // Range filtering
  if(distL < 5 || distL > 40) distL = -1;
  if(distR < 5 || distR > 40) distR = -1;

  Serial.print("L:");
  Serial.print(distL);
  Serial.print(" R:");
  Serial.println(distR);

  String gesture = detectGesture(distL, distR);

  // Store history
  history[histIndex] = gesture;
  histIndex = (histIndex + 1) % HISTORY_SIZE;

  String stable = getStableGesture();

  if(!gestureLock && stable != "")
  {
    Serial.println(stable);

    gestureLock = true;
    lastAction = millis();
  }

  // Reset lock when no hand present
  if(distL == -1 && distR == -1)
  {
    gestureLock = false;
  }

  delay(100);
}
