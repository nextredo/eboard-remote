## eBoard-remote
##### See progress log for more in-depth project information
- Coded by Kurtis Brandt in the year 2020

*********************************************************************
*********************************************************************
### Only use true-fixed-master branch
Pay absolutely no attention whatsoever to the other branches in this repository.  
They all have outdated code - the branch being updated is true-fixed-master
They were a series of cascading mistakes trying to fix the original mistake.  
See 22/07/2020 in the progress log for more details.  
Or don't.  
*********************************************************************
*********************************************************************

Project uses a generic ESP8266 board for control hardware.
- Espressif ESP8266 E-12 running Arduino.
- Board I used linked [here](https://www.banggood.com/Geekcreit-NodeMcu-Lua-WIFI-Internet-Things-Development-Board-Based-ESP8266-CP2102-Wireless-Module-p-1097112.html)

Communicates with eBoard using the ESP8266's onboard WiFi chip.
Once coding is finished, it will have the following features:
- Features can be found in **MENU + FEATURES.md** file in the master directory


*********************************************************************
### Onboard LEDs
[Info on LEDs](https://lowvoltage.github.io/2017/07/09/Onboard-LEDs-NodeMCU-Got-Two)  
Pin 2 (D4) = ESP-12 LED  
Pin 16 (D0) = NodeMCU LED  
Both have 470 ohm resistor  
*********************************************************************
### Screen
[Screen I bought](https://www.banggood.com/1_3-Inch-4Pin-White-OLED-LCD-Display-12864-IIC-I2C-Interface-Module-p-1067874.html)  
SSH1106 control chip (may or may not be the same as SH1106 chip)  
128x64 resolution  
1.3 inches (29.42 x 14.7mm)  
3.3 - 5v driving voltage  
I2C interface  

Red wire = VCC  
Black wire = GND  
Yellow wire = SCL  
Blue wire = SDA  

[OLED Relevant instructions](http://files.banggood.com/2016/07/banggood_OLED_Relevant_instructions.zip)
*********************************************************************
### Rotary encoder
[Encoder I bought](https://www.banggood.com/KEYES-360-Degree-Rotary-Encoder-Control-Module-Electronic-Building-Block-For-Micro-Bit-p-1400918.html)  
360 degree rotation + button  
5 pin interface (CLK, DT, SW, +, GND)  

Pin listings:
- CLK = pin A = one of the yellow wires = D5 (pin 5)
- DT = pin B = one of the yellow wires = D6 (pin 6)
- SW = button pin = blue wire = D7 (pin 7)
- GND and VCC respectively = red and black respectively