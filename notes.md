## Specialised Notes

### Screen
Exerpt from banggood's listing:  
About control chip SSH1106:  
SSH1106 compatible with SSD1306 basic, difference is that SSH1106 control chip RAM space is 132*64, while SSD1306 space is 128*64.  
The 1.3-inch OLED 128*64 dot matrix, so in the middle of the screen production took 128 row. When using SSD1306 program point SSH1106 screen, only need to change address to 0x02 row to start.  

U8g2 code for rotating the screen  
u8g2.setFlipMode(1)  
*********************************************************************
### Rotary enc
NOTE: This might not be the best way to do it - using a library can let you have interrupts among other cool features
also note that if you try to catch "ticks" in the main loop - if main takes too long then ticks will start to be missed
and so code doesn't really work out well

Info from [HowToMechatronics.com's rotary enc video](https://www.youtube.com/watch?v=v4BbSzJ-hz4&ab_channel=HowToMechatronics)  
- This is a 5 pin interface (incremental rotary encoder) (relative rotary encoder / quadrature encoder)
- Literally the exact same one as in the video
- A & B pins produce square waves - based upon contact of common pin C
- Output signals -> if equal then clockwise (if sampled every second time a change occurs on one of the pins)
- if unequal then counter clockwise

#### Interrupts  
- All pins have this excluding GPIO16 (D0 / pin 4)
- Modes are "external" and "pin change"
- Can trigger on rising or falling edges, or level changes
- When triggered: Exits from main loop, done some code stuff, then returns something back

Notes from [educ8s.tv's interrupt video](https://www.youtube.com/watch?v=QtyOiTw0oQc&ab_channel=educ8s.tv)  
- Interrupts let the microprocessor respond to something while doing something else
- ISR = interrupt service routine
- Triggered on rising / falling edge of digital pins (interrupt pins) - almost every pin on ESP2866 (GPIO 0 - 15)
- Example code found in the code backups section
- Use attachInterrupt function for it


## General Notes

### A note about libraries in PlatformIO
- I'm coding this in PlatformIO, which is a turbo beefed up Arduino IDE in Visual Studio Code
- It installs libraries through the platformio.ini file in master
- Since the actual libraries it uses are not actually being stored in the GitHub anywhere - if you use
this yourself on PIO, it'll automagically download and install the libraries due to the .ini file
- However, if using the Arduino IDE or something else, you'll have to download those libraries for yourself or
ask your IDE to do that some other way
- But seriously - please use PIO, it's a great IDE and I can't stress just how much better it is than the standard IDE
- Easier to use once you understand it, bit of a learning curve though

### Hyperlinks in markdown
A generic test [link](http://example.com "Title") in markdown

### Reset debugging
ESP.getResetReason()

### Floating pins
If a pin is neither connected to GND or HIGH, it'll return random values based upon interference when digitalRead  
Prevent with pull-up or pull-down resistor  

### ESP8266 vs ESP32
I'm definitely buying an ESP32 next time