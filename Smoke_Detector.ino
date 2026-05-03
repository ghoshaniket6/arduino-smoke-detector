/*
 * Smoke Detector Using Arduino
 * Project: B.Tech Undergraduate Project
 * Hardware: Arduino Uno, MQ-2 Smoke/Gas Sensor, Buzzer, LED, Enclosure Box
 *
 * Wiring:
 *   MQ-2 Analog Out  -> A0
 *   MQ-2 Digital Out -> D7  (optional threshold pin)
 *   Buzzer           -> D8
 *   Red LED (alarm)  -> D9
 *   Green LED (safe) -> D10
 *   VCC, GND         -> 5V, GND
 */

#define SMOKE_ANALOG_PIN  A0
#define SMOKE_DIGITAL_PIN 7
#define BUZZER_PIN        8
#define LED_RED_PIN       9
#define LED_GREEN_PIN     10

// Threshold: adjust after calibration (0-1023 scale)
// MQ-2 warm-up time is ~20 seconds after power-on
#define SMOKE_THRESHOLD   400

// Buzzer beep pattern
#define BEEP_INTERVAL_MS  300

unsigned long lastBeepTime = 0;
bool buzzerState = false;

void setup() {
  pinMode(SMOKE_DIGITAL_PIN, INPUT);
  pinMode(BUZZER_PIN,        OUTPUT);
  pinMode(LED_RED_PIN,       OUTPUT);
  pinMode(LED_GREEN_PIN,     OUTPUT);

  Serial.begin(9600);
  Serial.println("=== Smoke Detector Initialised ===");
  Serial.println("Warming up sensor (20 seconds)...");

  // Sensor warm-up indicator
  for (int i = 0; i < 20; i++) {
    digitalWrite(LED_GREEN_PIN, HIGH);
    delay(500);
    digitalWrite(LED_GREEN_PIN, LOW);
    delay(500);
  }

  Serial.println("Sensor ready. Monitoring started.");
}

void loop() {
  int smokeLevel = analogRead(SMOKE_ANALOG_PIN);

  Serial.print("Smoke Level: ");
  Serial.print(smokeLevel);

  if (smokeLevel >= SMOKE_THRESHOLD) {
    // ALARM STATE
    Serial.println(" — ALERT: Smoke Detected!");
    digitalWrite(LED_RED_PIN,   HIGH);
    digitalWrite(LED_GREEN_PIN, LOW);
    beepBuzzer();
  } else {
    // SAFE STATE
    Serial.println(" — Safe");
    digitalWrite(LED_RED_PIN,   LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);
    noTone(BUZZER_PIN);
    buzzerState = false;
  }

  delay(500);
}

// Non-blocking beep pattern for buzzer
void beepBuzzer() {
  unsigned long currentTime = millis();
  if (currentTime - lastBeepTime >= BEEP_INTERVAL_MS) {
    lastBeepTime = currentTime;
    buzzerState = !buzzerState;
    if (buzzerState) {
      tone(BUZZER_PIN, 1000); // 1kHz tone
    } else {
      noTone(BUZZER_PIN);
    }
  }
}
