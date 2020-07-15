eBoard-remote

Project uses a generic ESP8266 board for control hardware.
- Espressif ESP8266 E-12 running Arduino.

Communicates with eBoard using the ESP8266's onboard WiFi chip.
Once coding is finished, it will have the following features:
- 





*********************************************************************
Onboard LEDs

Pin 2 (D4) = ESP-12 LED
Pin 16 (D0) = NodeMCU LED
Both have 470 ohm resistor

https://lowvoltage.github.io/2017/07/09/Onboard-LEDs-NodeMCU-Got-Two - Info on LEDs
https://www.banggood.com/Geekcreit-NodeMcu-Lua-WIFI-Internet-Things-Development-Board-Based-ESP8266-CP2102-Wireless-Module-p-1097112.html - Board I bought


*********************************************************************
Screen

SSH1106 control chip
128x64 resolution
1.3 inches (29.42 x 14.7mm)
3.3 - 5v driving voltage
I2C interface

Red wire = VCC
Black wire = GND
Yellow wire = SCL
Blue wire = SDA

Device is initialised using U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
for the U8g2 library found here: https://github.com/olikraus/u8g2

OLED Relevant instructions downloaded from listing page - link below
https://www.banggood.com/1_3-Inch-4Pin-White-OLED-LCD-Display-12864-IIC-I2C-Interface-Module-p-1067874.html - Screen I bought
http://files.banggood.com/2016/07/banggood_OLED_Relevant_instructions.zip - Instructions that come with the screen

Exerpt from banggood's listing:
About control chip SSH1106:
SSH1106 compatible with SSD1306 basic, difference is that SSH1106 control chip RAM space is 132*64, while SSD1306 space is 128*64.
The 1.3-inch OLED 128*64 dot matrix, so in the middle of the screen production took 128 row. When using SSD1306 program point SSH1106 screen, only need to change address to 0x02 row to start.


*********************************************************************
Rotary encoder

360 degree rotation
5 pin interface (CLK, DT, SW, +, GND)

https://www.banggood.com/KEYES-360-Degree-Rotary-Encoder-Control-Module-Electronic-Building-Block-For-Micro-Bit-p-1400918.html - Encoder I bought