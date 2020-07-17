#define onboardLED 2
volatile boolean ledON = false;

#define PIN_A 9//9
#define PIN_B 10//10
#define BUTTON 14//14

//#include <RotaryEncoder.h>
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

void setup() {
  Serial.begin(115200);
  pinMode(onboardLED, OUTPUT);

  //encoder.begin();
  pinMode(PIN_A,      INPUT_PULLUP);
  pinMode(PIN_B,      INPUT_PULLUP);
  //pinMode(BUTTON,     INPUT_PULLUP);

  digitalWrite(PIN_A, HIGH); // Turns internal pull-up on
  digitalWrite(PIN_B, HIGH); // Turns internal pull-up on
  //digitalWrite(BUTTON, HIGH); // Turns internal pull-up on

  //attachInterrupt(digitalPinToInterrupt(PIN_A),  encoderISR,       CHANGE);  // call encoderISR()        every high->low or low->high   changes
  //attachInterrupt(digitalPinToInterrupt(BUTTON), encoderButtonISR, FALLING); // call encoderButtonISR()  every high->low                changes
}

void loop() {
  /*
  if(position != encoder.getPosition()) {
    position = encoder.getPosition();
    Serial.println(position);
  }
  
  if(encoder.getPushButton() == true) {
    Serial.println(F("PRESSED"));         //(F()) saves string to flash & keeps dynamic memory free
  }
  */
  Serial.println(millis());
  digitalWrite(onboardLED, HIGH);
  delay(150);
  digitalWrite(onboardLED, LOW);
  delay(150);
}
