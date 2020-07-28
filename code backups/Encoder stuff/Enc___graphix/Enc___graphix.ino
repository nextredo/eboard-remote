#include <Arduino.h>

// U8g2 code
#include <U8g2lib.h>
#include <Wire.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// ClickEncoder code
#include <ClickEncoder.h>
#define ENCODER_PINA               12 //GPIO12 (D6 / pin 6)
#define ENCODER_PINB               14 //GPIO14 (D5 / pin 5)
#define ENCODER_BTN                13 //GPIO13 (D7 / pin 7)
#define ENCODER_STEPS_PER_NOTCH    4  //Change this depending on which encoder is used
ClickEncoder encoder = ClickEncoder(ENCODER_PINA,ENCODER_PINB,ENCODER_BTN,ENCODER_STEPS_PER_NOTCH);


void u8g2_prepare(void) {
  //u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFont(u8g2_font_5x7_mf); // 6 px height (capital A) (need to make this bigger)
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

void setup() {
  Serial.begin(115200);
  
  // U8g2 code
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R3); //vertical for the housing it's in

  // ClickEncoder code
  encoder.setButtonHeldEnabled(true);
  encoder.setDoubleClickEnabled(true);
  encoder.setButtonOnPinZeroEnabled(true);
}

void loop() {
  static uint32_t lastService = 0;
  if (lastService + 1000 < micros()) {
    lastService = micros();                
    encoder.service();  
  }
  
  static int16_t last, value;
  value += encoder.getValue();
  if (value != last) {
    last = value;
    Serial.print("Encoder Value: ");
    Serial.println(value);
  }
  
  char s[3];
  itoa(value, s, 10); //integer, string to put it into, base of integer
  
  //u8g2.clearBuffer();
  //u8g2_prepare();
  //u8g2.drawStr(0, 0, "Hello World!");
  //u8g2.drawStr(0, 6+2, s);
  Serial.println(s);
  //u8g2.sendBuffer();
  delay(50);
}
