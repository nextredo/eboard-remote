#include <Arduino.h>

//#define onboardLED 2  // This is the ESP-12 LED (D4)
//#define NodeMCULED 16 // This is the NodeMCU LED (D0)
// Both LEDs come equipped with a 470 ohm resistor -- https://lowvoltage.github.io/2017/07/09/Onboard-LEDs-NodeMCU-Got-Two


// ----- Encoder code -----
//#include <RotaryEncoder.h>

#define PIN_A 5//12//9//16//5  // CLK pin
#define PIN_B 6//11//10//21//6  // DT pin
#define BUTTON 17//13//14//22//7 // SW (button) pin
// D8 used for boot process so don't use that pin

//int16_t position = 0;
//RotaryEncoder encoder(PIN_A, PIN_B, BUTTON);

/*
void ICACHE_RAM_ATTR encoderISR() { // interrupt service routines need to be in ram
  encoder.readAB();
}
void ICACHE_RAM_ATTR encoderButtonISR() {
  encoder.readPushButton();
}
*/



//int testCount = 0;
void setup() {
  Serial.begin(115200); //always use this baud rate - it's the default (monitor_speed = 115200)

  // encoder code
  //encoder.begin(); // set encoders pins as input & enable built-in pullup resistors
  // this function seems to break the ESP8266 - let's try by ourselves
  pinMode(PIN_A,      INPUT_PULLUP);
  pinMode(PIN_B,      INPUT_PULLUP);
  pinMode(BUTTON,     INPUT_PULLUP);


  //attachInterrupt(digitalPinToInterrupt(PIN_A),  encoderISR,       CHANGE);  // call encoderISR()        every high->low or low->high   changes
  //attachInterrupt(digitalPinToInterrupt(BUTTON), encoderButtonISR, FALLING); // call encoderButtonISR()  every high->low                changes
}

void loop() {  
  /*
  Serial.println(testCount++);
  if(position != encoder.getPosition()) {
    position = encoder.getPosition();
    Serial.println(position);
  }
  
  if(encoder.getPushButton() == true) {
    Serial.println(F("PRESSED"));         //(F()) saves string to flash & keeps dynamic memory free
    testCount = 0;
  }
  */
  Serial.println(millis());
  delay(5);
}

































