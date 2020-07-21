## 22/07/2020
- Was experiencing MAJOR issues with pushing stuff to the GitHub page
	- Something about a pre-hook error??
	- Unsure what that means at all
- After having created 5 or so branches to try and fix this damn thing, I figured out the issue
- The push failure was due to a file that was far too big for GitHub to handle
	- I'd downloaded a zip file for an installer for a program called [Visuino](https://www.visuino.com/) which was about 133MB
	- Apparently the [max file size](https://stackoverflow.com/questions/38768454/repository-size-limits-for-github-com#:~:text=Repositories%20have%20a%20hard%20size%20limit%20of%20100GB.&text=In%20addition%2C%20we%20place%20a%20strict%20maximum%20size%20limit%20of,a%20link%20to%20the%20repos.) for a single file on GitHub is 100MB
		- Aaaaand since this file exceeded it, my computer would spend 10 minutes trying to upload the whole thing and then tell me it failed right at the end of it all
	- I've messed around with this so much that time literally has no meaning now for these pushes


## 21/07/2020
### Library 1
- Trying a new encoder library - found [here](https://github.com/PaulStoffregen/Encoder)
	- More detailed information about it found [here](https://www.pjrc.com/teensy/td_libs_Encoder.html)
- Uploaded the code and once again - our old friend the WDT reset rears its ugly head
	- Trying adding `digitalPinToInterrupt()` to the header file's `attachInterrupt()` functions
	- Apparently reset is caused by `rst cause:2` - ie the reset pin
	- Giving up on this library - moving to another
	
### Library 2
- Trying [this](https://github.com/dimircea/REncoder) one
- Changed the following in `REncoderConfig.h`
	- Uncommented `#define RENCODER_ENABLE_ENCODER_IRQ`
	- Uncommented `#define RENCODER_ENABLE_SWITCH_IRQ`

- To answer your question - of course it doesn't work
	- This function here `attachSwitchHandler` somehow isn't defined, even though it is
	- Using the file `REncoderWithSwitch.cpp`
	
- Ok so it turns out I had 2 copies of the library and I was defining things in the wrong one
- New error is something about converting `'setup()::__lambda1' to 'void (*)(REncoderWithoutSwitch::Event, RENCODER_ROTATION_VALUE_TYPE) {aka void (*)(REncoderWithoutSwitch::Event, int)}'`
	- I have literally 0 idea how to fix this so I'm just going to give up
	- I should learn to code Arduino libraries so I can understand them better
	
### Library 3
- [ClickEncoder](https://github.com/soligen2010/encoder)
- And finally at last - one that works absolutely perfectly
	- Software debouncing working like a dream
	- Now that the encoder finally works properly - I'll start on the potentiometer, which shouldn't be too hard
	- Velocity scaling of encoder rotation values has a bit too long of a running average time - might ened to tweak that a tad

### Potentiometer
- Wrote a small sketch to measure the potentiometer values
	- Since it's already setup in the remote housing, it was pretty chill
- Measurements for avg, max and min are below:
	- Average value is 550 - 525
		- 550 if coming from max reverse
		- 525 if coming from max accel
	- Max accel value is 412
	- Max decel value is 615
- All measured values very constant
- Now that that's all sorted, I'm working on what's in the to do list
	- First order of business is features and menu stuff
	

## 19/07/2020
- Further testing encoder library code to see when interrupts are triggered versus when the output is "tripped"
	- Doing anything generally leads to loads of triggers ocurring
		- encoderISR triggering behaviour
			- Triggers once on turning "onto" pin
			- Triggers twice or once coming "off" pin
		- encoderButtonISR behaviour
			- Triggers once on button push down
			- Triggers 4-5 times on button release
	- Adding more capacitance to the button made it worse
		- The extra 1uF cap in parallel made the ISRs more likely to interrupt the printing of PRESSED to the serial monitor
	- [This link](https://www.best-microcontroller-projects.com/rotary-encoder.html) could be useful for debounce
- Unrelated note: I'm going to re-organise my desk to make it a bit easier to debug this sort of stuff


## 18/07/2020
- Starting to think I'm using the wrong numbers to define my pins - requires further investigation
	- Great resource about pin definitions by thehookup [here](https://github.com/thehookup/Wireless_MQTT_Doorbell/blob/master/GPIO_Limitations_ESP8266_NodeMCU.jpg) from [this video](https://www.youtube.com/watch?v=7h2bE2vNoaY&t=60s&ab_channel=TheHookUp)
	- [There's one for the ESP32 too](https://github.com/thehookup/ESP32_Ceiling_Light/blob/master/GPIO_Limitations_ESP32_NodeMCU.jpg)
	- Going to try using the GPIO numbers as definitions like he does in the video
### AAAAAAAAAAAAAAAAAAAAAAHHHHHHHH
- Turns out I was using the wrong numbers for the pins
	- You're meant to use the GPIO number (GPIO2 for example) NOT the other little grey pin number
- Resoldered A, B and BUTTON
	- PIN_A = GPIO12 (D6)
	- PIN_B = GPIO14 (D5)
	- BUTTON = GPIO13 (D7)
### Starting to work
- Now the encoder is working, but the values are bouncing all over the place
	- Only registers half the turn increments
	- Registers far too many button presses
- Adding a 100nF/0.1μF capacitor between each pin and GND like it says is req'd in the README
	- Found some on an old circuit board and used those
- Soldered 0.01μF caps to A and B, and a 0.1μF to BUTTON
	- Somehow, this made it worse
		- Button now triggers far more when pressed only once
		- turning L and R barely registers unless I turn it super fast

- Added some clamp probes to my multimeter - this is going to make things much easier

## 17/07/2020
Begun this progress log at about 7pm (finished about 1am the next day), realised I needed it as I'd just been dumping my notes and basic progress
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

### 3rd time's the charm 
- [link to enjoyneering's repo](https://github.com/enjoyneering/RotaryEncoder)
- Implemented the code from the ESP8266RotaryEncoderInterruptsSerial example .ino file
- immediately caused the ESP8266 to bootloop
	- trying to diagnose the problem by commenting out the new code and slowly adding it back in
	- problem due to line `encoder.begin();`
	- `encoder.begin();` causes the following to appear in the serial monitor
	
	```
	ets Jan  8 2013,rst cause:4, boot mode:(3,7)  
	wdt reset  
	load 0x4010f000, len 3664, room 16  
	tail 0  
	chksum 0xee  
	csum 0xee  
	v39c79d9b  
	~ld  
	```
	
	- This is a WDT reset, info about debugging them [here](https://arduino-esp8266.readthedocs.io/en/latest/faq/a02-my-esp-crashes.html#:~:text=Enable%20the%20Out%2DOf%2DMemory,showing%20up%20on%20each%20restart.)
	- Information on boot modes [here](https://arduino-esp8266.readthedocs.io/en/latest/boards.html#boot-messages-and-modes)
		- Shows us that `rst cause:4, boot mode:(3,7)` means:
		- rst cause is a watchdog reset
		- The 3 low bits of x in `boot mode:(x,y)` correspond to MTDO, GPIO0 and GPIO2 - [link](https://github.com/esp8266/esp8266-wiki/wiki/Boot-Process)
			- 3 in binary is 011, corresponding to MTDO = 0, GPIO 0&2 = 1
			- Means ESP8266 is booting in SPI Flash mode	

*********************************************************************
- tracing the `encoder.begin()` function to `RotaryEncoder.cpp` reveals that all it does is set the pins as inputs
with their pullup resistors on
- testing this code straight in void setup reveals that it still breaks it
- if we move them to regular inputs (`pinMode` `INPUT` instead of `INPUT_PULLUP`), it's still broken
- It was found that by swapping the rotary encoder pins to pin 16, 21, 22 (GPIO 15, GPIO3 and GPIO1 respectively), the program operates fine
	- Odd considering GPIO 1 & 3 are used for TX and RX, and thus UART / Serial communications  

*********************************************************************
- ESP seems to be happy when using pins 9, 10 and 14 (CMD, SD0 and CLK) (GPIO11, GPIO7 and GPIO6)
- Resoldered `PIN_A`, `PIN_B` and `BUTTON` (CLK, DT and SW) to 9, 10 and 14
- Didn't fix the issues, just changed them
- Restarting `min.cpp` code to see if I can fix it there

*********************************************************************
- Set code to literally only define pins and set them as inputs, still breaks if 12, 11 and 13 are used
- Same story for 5, 6 and 7
- and 5, 6, 17

*********************************************************************
- Here's the story so far
	- Works somehow on 9, 10 and 14
	- Works with the following code (so long as no pins are connected to VCC or GND)
	```
	#define onboardLED 2
	volatile boolean ledON = false;

	#define PIN_A 9
	#define PIN_B 10
	#define BUTTON 14 //17

	#include <RotaryEncoder.h>
	int16_t position = 0;
	RotaryEncoder encoder(PIN_A, PIN_B, BUTTON);


	void setup() {
	  Serial.begin(115200);
	  pinMode(onboardLED, OUTPUT);
	  
	  pinMode(PIN_A,      INPUT_PULLUP);
	  pinMode(PIN_B,      INPUT_PULLUP);
	  pinMode(BUTTON,     INPUT_PULLUP);
	}

	void loop() {
	  Serial.println(millis());
	  digitalWrite(onboardLED, HIGH);
	  delay(150);
	  digitalWrite(onboardLED, LOW);
	  delay(150);
	}
	```