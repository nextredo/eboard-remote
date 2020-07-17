#include <Arduino.h>
#define onboardLED 2  // This is the ESP-12 LED (D4)

#define pinA 5 // CLK pin, GPIO14
#define pinB 6 // DT pin, GPIO12
#define pinP 7 // SW (button) pin, GPIO13
// interrupts don't work on GPIO16

volatile bool combinedState = false;

void setup() {
	pinMode(onboardLED, OUTPUT);
	
	// interrupt pins
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	pinMode(pinC, INPUT);
	
	attachInterrupt(digitalPinToInterrupt(pinA), AorBRising, RISING);
	attachInterrupt(digitalPinToInterrupt(pinB), AorBRising, RISING);
	// calls the same function if any of the pins experience a rising edge
	
}

void main() {
	
}


void AorBRising() {
	// for the rising edge of the pin A signal:
	// if A = B then turning left
	// if A != B then turning right
	// ****************************************
	// for the rising edge of the pin B signal:
	// if B = A then turning left
	// if B != A then turning right
	combinedState = ( digitalRead(pinA) & digitalRead(pinB) )
	switch (combinedState) {
		case 0: // enc is turning right
			//decrementEnc();
			break;
		case 1: // enc is turning left
			//incrementEnc();
			break;
	}
}