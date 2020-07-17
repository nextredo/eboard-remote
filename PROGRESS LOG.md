## 17/7/2020
- Begun this progress log at about 7pm, realised I needed it as I'd just been dumping my notes and basic progress
into my README file - probably not great practice
- Also put a whole bunch of stuff into notes.md

- Resoldered connector for rotary enc
	- Swapped + & -
	- Moved SW to D5 from VCC
- Experimented with various libraries;
### Library 
- Decided to use [this](https://github.com/John-Lluch/Encoder) one since John talks a big game and I like it
- This is in the lib directory of my master eBoard-remote folder
- Scratch that - not using this library as it won't work even with the sample code

### Actual library  
- Using [this](https://github.com/brianlow/Rotary) one because it doesn't look tooooo complicated
- couldn't get it to work with PIO, scratch that

### No for real this time 
- [link to enjoyneering's repo](https://github.com/enjoyneering/RotaryEncoder)
- Implemented the code from the ESP8266RotaryEncoderInterruptsSerial example .ino file
- immediately caused the ESP8266 to bootloop
	- trying to diagnose the problem by commenting out the new code and slowly adding it back in
	- problem due to line `encoder.begin();`
	- `encoder.begin();` causes the following to appear in the serial monitor:
	
	
	 ets Jan  8 2013,rst cause:4, boot mode:(3,7)

	wdt reset
	load 0x4010f000, len 3664, room 16
	tail 0
	chksum 0xee
	csum 0xee
	v39c79d9b
	~ld
	
	- This is a WDT reset, info about debugging them [here](https://arduino-esp8266.readthedocs.io/en/latest/faq/a02-my-esp-crashes.html#:~:text=Enable%20the%20Out%2DOf%2DMemory,showing%20up%20on%20each%20restart.)
	- Information on boot modes [here](https://arduino-esp8266.readthedocs.io/en/latest/boards.html#boot-messages-and-modes)
		- Shows us that `rst cause:4, boot mode:(3,7)` means:
		- rst cause is a watchdog reset
		- The 3 low bits of x in `boot mode:(x,y)` correspond to MTDO, GPIO0 and GPIO2 - [link](https://github.com/esp8266/esp8266-wiki/wiki/Boot-Process)
			- 3 in binary is 011, corresponding to MTDO = 0, GPIO 0&2 = 1
			- Means ESP8266 is booting in SPI Flash mode
	
	
- tracing the `encoder.begin()` function to `RotaryEncoder.cpp` reveals that all it does is set the pins as inputs
with their pullup resistors on
- testing this code straight in void setup reveals that it still breaks it
- if we move them to regular inputs (`pinMode` `INPUT` instead of `INPUT_PULLUP`), it's still broken
- It was found that by swapping the rotary encoder pins to pin 16, 21, 22 (GPIO 15, GPIO3 and GPIO1 respectively), the program operates fine
	- Odd considering GPIO 1 & 3 are used for TX and RX, and thus UART / Serial communications

- ESP seems to be happy when using pins 9, 10 and 14 (CMD, SD0 and CLK) (GPIO11, GPIO7 and GPIO6)
- Resoldered `PIN_A`, `PIN_B` and `BUTTON` (CLK, DT and SW) to 9, 10 and 14
- Didn't fix the issues, just changed them
- Restarting `min.cpp` code to see if I can fix it there

- Set code to literally only define pins and set them as inputs, still breaks if 12, 11 and 13 are used
- Same story for 5, 6 and 7
- and 5, 6, 17

- Here's the story so far
	- Works with just pin A (on pin 5) as input pullup
	- Works with just pin B (on pin 9) as input pullup