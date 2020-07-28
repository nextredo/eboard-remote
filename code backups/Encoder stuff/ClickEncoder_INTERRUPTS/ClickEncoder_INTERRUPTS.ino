#define onboardLED 2
volatile boolean ledON = false;

#define PIN_A 12 //GPIO12 (D6 / pin 6)
#define PIN_B 14 //GPIO14 (D5 / pin 5)
#define BUTTON 13 //GPIO13 (D7 / pin 7)

///*
void ICACHE_RAM_ATTR encoderISR() { // interrupt service routines need to be in ram
  Serial.println("encoderISR TRIGGERED");
  // custom code goes here
}
void ICACHE_RAM_ATTR encoderButtonISR() {
  Serial.println("encoderButtonISR TRIGGERED");
  // custom code goes here
}
//*/

void setup() {
  Serial.begin(115200);
  pinMode(onboardLED, OUTPUT);

  //encoder.begin();
  //pinMode(PIN_A,      INPUT_PULLUP);
  //pinMode(PIN_B,      INPUT_PULLUP);
  //pinMode(BUTTON,     INPUT_PULLUP);

  //digitalWrite(PIN_A, HIGH); // Turns internal pull-up on
  //digitalWrite(PIN_B, HIGH); // Turns internal pull-up on
  //digitalWrite(BUTTON, HIGH); // Turns internal pull-up on

  attachInterrupt(digitalPinToInterrupt(PIN_A),  encoderISR,       CHANGE);  // call encoderISR()        every high->low or low->high   changes
  attachInterrupt(digitalPinToInterrupt(BUTTON), encoderButtonISR, FALLING); // call encoderButtonISR()  every high->low                changes
}

void loop() {
  ///*
  if(position != encoder.getPosition()) {
    position = encoder.getPosition();
    Serial.println(position);
  }
  
  if(encoder.getPushButton() == true) {
    Serial.println(F("PRESSED"));         //(F()) saves string to flash & keeps dynamic memory free
  }
  //*/

  /*
  Serial.println(millis());
  digitalWrite(onboardLED, HIGH);
  delay(400);
  
  digitalWrite(onboardLED, LOW);
  delay(400);
  */
}
