#define potPin A0 //2 //the only ADC pin on the board, ADC0 (A0)

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Potvalue = ");
  Serial.println(analogRead(potPin));
  delay(10);
}
