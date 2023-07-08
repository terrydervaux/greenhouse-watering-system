#include <Arduino.h>

#define PIN_LED 16

// put function declarations here:
int blinkLED(int);

void setup() {
  // setup LED
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int result = blinkLED(2000);
}


int blinkLED(int delayValue) {
  
  if(delay > 0) {
    digitalWrite(PIN_LED, HIGH);
    delay(delayValue);
    digitalWrite(PIN_LED, LOW);
    return 0;
  }

  return 1;
}