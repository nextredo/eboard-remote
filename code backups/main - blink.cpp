#include <Arduino.h>

#define onboardLED 2  // This is the ESP-12 LED (D4)
#define NodeMCULED 16 // This is the NodeMCU LED (D0)
// Both LEDs come equipped with a 470 ohm resistor -- https://lowvoltage.github.io/2017/07/09/Onboard-LEDs-NodeMCU-Got-Two

void setup() {
  pinMode(onboardLED, OUTPUT);
}

void loop() {
  digitalWrite(onboardLED, HIGH);
  delay(500);
  digitalWrite(onboardLED, LOW);
  delay(500);
}