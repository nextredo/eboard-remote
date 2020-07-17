#define onboardLED 2

#define PIN_A 5
#define PIN_B 9 //6
#define BUTTON 7 //17

void setup() {
  Serial.begin(115200);
  pinMode(onboardLED, OUTPUT);
  
  pinMode(PIN_A,      INPUT_PULLUP);
  pinMode(PIN_B,      INPUT_PULLUP);
  //pinMode(BUTTON,     INPUT_PULLUP);
}

void loop() {
  Serial.println(millis());
  digitalWrite(onboardLED, HIGH);
  delay(150);
  digitalWrite(onboardLED, LOW);
  delay(150);
}
