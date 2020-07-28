## Pseudocode
- Mix between Arduino (C/C++) and plain english
- Interesting ideas
	- Branchless programming (optimisation)
	- Ways of using obscure C and C++ functions for performance increases
*********************************************************************
## Things the board has to do
- Accelerate
- Brake
- Trigger smoothing
- Comms
	- Heartbeat
	- Failsafe management
	- 

## Things the code has to do
- WiFi
	- Communicate with board
		- Send potentiometer data (scaled)
		- Failsafe management
			- Disconnect / brown-out
			- Illegal values
			- Low battery (remote or board)
		- Board settings
	- Local settings
- Screen
	- Splash screen
	- Main screen
		- Mode (can change)
		- Speed
		- Connection status
		- Throttle value
		- Encoder engaged / disengaged
		- Board battery charge
	- Menu system
		- Modes
			- Select mode
				- Eco
				- Cruise
				- Balanced
				- Hi Pwr
			- Braking modes
		- Main menu
			- Comms
				- Re-bind board
			- Trigger settings
				- Trigger setup (stepped process)
					- Re-centre
					- Deadzone adjust
					- Max and min adjust
- Encoder
	- Use for menu / settings interaction
- Potentiometer
	- Trigger

## Main vs loops
- Things that must be done in main()
	- Encoder reading
- Things that can be done in functions (or interrupts)
	- Screen updates
		- Main
		- Menu + submenus
	- WiFi sending
		- Heartbeat etc
	- Pot reading
		- That's literally the only thing the pot is used for
		- That's it

## Pseudocode itself

```
Initials  

#include <Arduino.h>  
#include <ClickEncoder.h>  

#include <U8g2lib.h>  
#include <Wire.h> // as U8X8_HAVE_HW_I2C is defined (#ifdef)  
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  

#define MAIN 0;  
#define MENU 1;  
#define COMMS 2;  
#define MODES 3;  
#define TRIG 4;  

// Screen pins defined by U8g2  
// WiFi stuff built into chip  

Pin definitions  
#define potPin A0  

#define PIN_A  12 //GPIO12 (D6 / pin 6)  
#define PIN_B  14 //GPIO14 (D5 / pin 5)  
#define BUTTON 13 //GPIO13 (D7 / pin 7)  

draw();  
drawSubmenu();  

void setup() {  
	Serial.begin(115200);  
	
	u8g2.begin();  
	
	encoder.setButtonHeldEnabled(true);  
	encoder.setDoubleClickEnabled(true);  
	encoder.setButtonOnPinZeroEnabled(true);  
	
	SPLASH SCREEN  
	
	INITIALISE WIFI  
	CONNECT TO BOARD  
	IF CAN'T CONNECT TO BOARD  
		drawSubmenu(BIND);
	ENDIF  
}  

void main() {  
	SERVICE ENCODER  
	GET ENCODER VALUES  
	SEND ENCODER VALUES  
	
	IF ENCODER DOUBLE CLICKED  
		draw(MENU);  
	ENDIF  
	
	IF DISPLAY UPDATE NEEDED  
		draw(MAIN);  
	ENDIF  
	
	SEND TRIGGER VALUES  
}  

// ***********************************************************************************  
// drawing functions  
// ***********************************************************************************  

void draw(menu_state) {  
	switch(menu_state) {  
		case MAIN: mainScrn(); break;  
		case MENU: menuScrn(); break;  
		case COMMS: commsMenu(); break;  
		case MODES: modesMenu(); break;  
		case TRIG: trigMenu(); break;  
	}  
}  

void drawSubmenu() {  
	switch(submenu_state) {  
	// COMMS  
		case BIND: comms_Bind(); break;  
	// MODES  
		case MODE_SELECT: modes_Select(); break;  
	// TRIGGER   
		case TRIG_SETUP: trig_Setup(); break;  
	}  
}  

// ***********************************************************************************  
// settings functions  
// ***********************************************************************************  


// ***********************************************************************************  
// misc functions (pot reading func, communications funcs, encoder funcs)  
// ***********************************************************************************  

```