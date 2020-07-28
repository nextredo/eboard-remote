#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void setup() {
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R3); //vertical for the housing it's in
}

void loop() {
  u8g2.clearBuffer();
  u8g2_prepare();
  u8g2.drawStr(0, 0, "Hello World!");
  u8g2.sendBuffer();
  delay(500);
}
