#include <Arduino.h>
#include <ClickEncoder.h>
//#include <TimerOne.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#define onboardLED 2  // This is the ESP-12 LED (D4)
#define NodeMCULED 16 // This is the NodeMCU LED (D0)

// ------------------------------ ClickEncoder ------------------------------
#define PIN_A                      12 //GPIO12 (D6 / pin 6)
#define PIN_B                      14 //GPIO14 (D5 / pin 5)
#define BUTTON                     13 //GPIO13 (D7 / pin 7)
#define ENCODER_STEPS_PER_NOTCH    4  // Change this depending on which encoder is used
ClickEncoder encoder = ClickEncoder(PIN_A, PIN_B, BUTTON, ENCODER_STEPS_PER_NOTCH);

int16_t encLast = 0;
int16_t encValue = 0;


// ---------------------------------- U8g2 ----------------------------------
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R3, /* reset=*/ U8X8_PIN_NONE);
// Initialise w rotation 3 and no U8X8 pin

// *************************************************************************************************
// *************************************************************************************************
// *************************************************************************************************
// *************************************************************************************************

void u8g2_prepare(void) {
  //u8g2.setFont(u8g2_font_6x10_tf);
  //u8g2.setFont(u8g2_font_5x7_mf);
  //u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.setFont(u8g2_font_9x18_mf);
  /*
   * t = transparent font
   * h = all glpyhs common height
   * m = all glyphs common height + width
   * 8 = all glpyhs fit into 8x8 pixel box
   * 
   * f = includes 256 glyphs
   * r = only glyphs in range of 32 - 127 in ASCII
   * u = only glyphs in 32 - 95 (uppercase) in ASCII
   * n = only numbers + extra glyphs for writing date and time strings
   */
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}


/*
void ICACHE_RAM_ATTR encoderISR() { // interrupt service routines need to be in ram
  encValue += encoder.getValue();
  
  if (encValue != encLast) {
    encLast = encValue;
    Serial.print("Encoder Value: ");
    Serial.println(encValue);
  }
  Serial.println("encoderISR TRIGGERED");
  // custom code goes here
}
void ICACHE_RAM_ATTR encoderButtonISR() {
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
  Serial.println("encoderButtonISR TRIGGERED");
  // custom code goes here
}
*/

// *************************************************************************************************
// *************************************************************************************************
// *************************************************************************************************
// *************************************************************************************************

void setup() {
  Serial.begin(115200);
  u8g2.begin();
  
  //u8g2.setDisplayRotation(U8G2_R3); //vertical for the housing it's in
  //pinMode(PIN_A,      INPUT_PULLUP);
  //pinMode(PIN_B,      INPUT_PULLUP);
  //pinMode(BUTTON,     INPUT_PULLUP);

  encoder.setButtonHeldEnabled(true);
  encoder.setDoubleClickEnabled(true);
  encoder.setButtonOnPinZeroEnabled(true);

  //attachInterrupt(digitalPinToInterrupt(PIN_A),  encoderISR,       CHANGE);  // call encoderISR()        every high->low or low->high   changes
  //attachInterrupt(digitalPinToInterrupt(BUTTON), encoderButtonISR, FALLING); // call encoderButtonISR()  every high->low                changes
}

void loop() {
  //Call Service in loop becasue using timer interrupts may affect ESP8266 WIFI
  //however call no more than 1 time per millisecond to reduce encoder bounce
  static uint32_t lastService = 0;
  if (lastService + 1000 < micros()) {
    lastService = micros();                
    encoder.service();  
  }
  
  u8g2.clearBuffer();
  u8g2_prepare();
  u8g2.drawStr(0, 0, "Hello");
  u8g2.drawStr(0, 12+2, "World");
  u8g2.sendBuffer();
 
  // ------------------------------ ClickEncoder ------------------------------
  static int16_t last, value;
  value += encoder.getValue();
  
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



  //delay(70);
  //Serial.println("looped");
}