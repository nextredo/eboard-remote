/*
 
This example demonstrates the use of the library on an ESP8266. without using a timer interrupt

 */

#include <ClickEncoder.h>
#include <TimerOne.h>
int16_t last, value;

//#define PIN_A 12 //GPIO12 (D6 / pin 6)
//#define PIN_B 14 //GPIO14 (D5 / pin 5)
//#define BUTTON 13 //GPIO13 (D7 / pin 7)

#define ENCODER_PINA     12
#define ENCODER_PINB     14
#define ENCODER_BTN      13

#define ENCODER_STEPS_PER_NOTCH    4   // Change this depending on which encoder is used

ClickEncoder encoder = ClickEncoder(ENCODER_PINA,ENCODER_PINB,ENCODER_BTN,ENCODER_STEPS_PER_NOTCH);

void setup() {
  Serial.begin(115200);

  encoder.setButtonHeldEnabled(true);
  encoder.setDoubleClickEnabled(true);
  encoder.setButtonOnPinZeroEnabled(true);
  last = -1;
}

void loop() { 
  //Call Service in loop becasue using timer interrupts may affect ESP8266 WIFI
  //however call no more than 1 time per millisecond to reduce encoder bounce
  static uint32_t lastService = 0;
  if (lastService + 1000 < micros()) {
    lastService = micros();                
    encoder.service();  
  }

  value += encoder->getValue();  
  if (value != last) {
    last = value;
    Serial.print("Encoder Value: ");
    Serial.println(value);
  }
  
  ClickEncoder::Button b = encoder.getButton();
  if (b != ClickEncoder::Open) {
    Serial.print("Button: ");
    #define VERBOSECASE(label) case label: Serial.println(#label); break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Pressed);
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)
      VERBOSECASE(ClickEncoder::Clicked)
      VERBOSECASE(ClickEncoder::DoubleClicked)
    }
  }    
}
