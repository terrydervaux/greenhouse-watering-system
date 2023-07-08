#include <Arduino.h>

#define LED_BUILTIN 16

// put function declarations here:
int blinkLED(int);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int result = blinkLED(2000);
}


int blinkLED(int delayValue) {
  
  if(delay > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(delayValue);
    digitalWrite(LED_BUILTIN, LOW);
    return 0;
  }

  return 1;
}