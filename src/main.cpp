#include <Arduino.h>

#define PIN_LED 16
#define PIN_RELAY 5

bool blinkLED(int);
bool activateRelay(bool);

void setup() {
  // setup serial port
  Serial.begin(115200);
  Serial.println("Serial port configured!");

  // setup LED
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // setup Relay
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);
}

void loop() {
  blinkLED(2000);
  
  activateRelay(true);
  delay(10000);
  activateRelay(false);
  delay(10000);
}

bool blinkLED(int delayValue) {
  if(delay > 0) {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("LED turned ON!");
    delay(delayValue);
    digitalWrite(PIN_LED, LOW);
    Serial.println("LED turned OFF!");
    return true;
  }
  return false;
}

bool activateRelay(bool activate) {
  if(activate){
    digitalWrite(PIN_RELAY, HIGH);
    Serial.println("Relay turned ON!");
    return true;
  }
  digitalWrite(PIN_RELAY, LOW);
  Serial.println("Relay turned OFF!");
  return false;
}
