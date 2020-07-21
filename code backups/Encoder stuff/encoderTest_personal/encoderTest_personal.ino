#include <Arduino.h>
#define onboardLED 2  // This is the ESP-12 LED (D4)

#define PIN_A 12 //GPIO12 (D6 / pin 6)
#define PIN_B 14 //GPIO14 (D5 / pin 5)
#define BUTTON 13 //GPIO13 (D7 / pin 7)

volatile bool combinedState = false;



void ICACHE_RAM_ATTR btnPressed() {
  Serial.println("btn");
}

void ICACHE_RAM_ATTR AorBRising() {
  // for the rising edge of the pin A signal:
  // if A = B then turning left
  // if A != B then turning right
  // ****************************************
  // for the rising edge of the pin B signal:
  // if B = A then turning left
  // if B != A then turning right
  combinedState = ( digitalRead(PIN_A) & digitalRead(PIN_B) );
  switch (combinedState) {
    case 0: // enc is turning right
      //decrementEnc();
      Serial.println("R");
      break;
    case 1: // enc is turning left
      //incrementEnc();
      Serial.println("L");
      break;
  }
}




void setup() {
  Serial.begin(115200);
  pinMode(onboardLED, OUTPUT);
  
  // interrupt pins
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(BUTTON, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(PIN_A), AorBRising, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_B), AorBRising, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON), btnPressed, RISING);
  // calls the same function if any of the pins experience a rising edge
  
}

void loop() {
  delay(5);
}
