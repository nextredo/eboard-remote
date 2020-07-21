#include <Arduino.h>

volatile boolean ledON = false;

#define onboardLED 2  // This is the ESP-12 LED (D4)
#define NodeMCULED 16 // This is the NodeMCU LED (D0)
// Both LEDs come equipped with a 470 ohm resistor -- https://lowvoltage.github.io/2017/07/09/Onboard-LEDs-NodeMCU-Got-Two

#define inputPin 7


void setup() {
	pinMode(inputPin, INPUT);
	pinMode(onboardLED, OUTPUT);
	attachInterrupt(0, buttonPressed, RISING);
	// 1st argument = interrupt ID (corresponds to a pin number)
	// 2nd argument = function (ISR) that will be executed when the interrupt is triggered (ISR = interrupt service routine)
	// 3rd argument = trigger mode (on rising or falling edge of signal (RISING / FALLING) (or level change - CHANGE))
	// --> change = triggers whenever the state changes (high to low OR low to high)
}

void main() {
	// ISR (interrupt service routine) etiquette
	// --> keep it short
	// --> no delays
	// --> no Serial.print functions
	// --> vars shared with main code should be volatile
	
	// volatile definition
	// --> this is a kind of variable qualifier
	// --> it's a directive to the compiler
	// --> tells the compiler to load said variable from RAM and NOT a storage register
	// --> sometimes vars stored in registers can be inaccurate
	// --> ****************************************************
	// --> if the var being stored is longer than a byte then the MCU can't read it in one shot since it's an 8-bit MCU
	// --> this can lead to the variable changing halfway through the code as the main function changes it while an interrupt is ocurring
	// --> to stop this from happening, use noInterrupts or the ATOMIC_BLOCK macro
	// -->  --> this stops the vars from being modified during an ISR
	// -->  --> can re-enable interrupts with interrupts()
}

void buttonPressed() {
	if(ledON) {
		ledON = false;
		digitalWrite(onboardLED, LOW);
	} else {
		ledON = true;
		digitalWrite(onboardLED, HIGH);
	}
}