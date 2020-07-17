## Current to do:
### Important
- ADC input capped at 1v
	- Need voltage divider so pot doesn't damage the chip
- Logic is 3.3v
	- Connect rotary enc to 3.3v and pot too

*********************************************************************
### Progression
Fix WDT reset error
	- Main issues
		- Unpredictable refusal to run code if certain pins are declared as inputs
		- Crashes and hangs once pins are bridged
		- INPUT vs INPUT_PULLUP not having an effect on the floating voltages of the pins
			- I think I just have to swap the encoder pins back to pins 5, 6, 7 and find a miracle way to make that work

Down the track sometime
- Potentiometer reading
- ESP8266 WiFi testing
- Pseudocode for whole remote