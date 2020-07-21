## Pseudocode
- Mix between Arduino (C/C++) and plain english
*********************************************************************

```
Initials  

#include <Arduino.h>
#include <ClickEncoder.h>

#include <U8g2lib.h>
#include <Wire.h> // as U8X8_HAVE_HW_I2C is defined (#ifdef)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Screen pins defined by U8g2
// WiFi stuff built into chip

Pin definitions
#define potPin A0

#define ENCODER_PINA     12 //GPIO12 (D6 / pin 6)
#define ENCODER_PINB     14 //GPIO14 (D5 / pin 5)
#define ENCODER_BTN      13 //GPIO13 (D7 / pin 7)

void setup() {  
	Serial.begin(115200);
	
	u8g2.begin();
	
	encoder.setButtonHeldEnabled(true);
	encoder.setDoubleClickEnabled(true);
	encoder.setButtonOnPinZeroEnabled(true);	
}

void main() {  

}

```