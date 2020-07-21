#define onboardLED 2
volatile boolean ledON = false;

#define PIN_A 12 //GPIO12 (D6 / pin 6)
#define PIN_B 14 //GPIO14 (D5 / pin 5)
#define BUTTON 13 //GPIO13 (D7 / pin 7)

/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(PIN_A, PIN_B);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(115200);
  pinMode(onboardLED, OUTPUT);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
    if(ledON) {
      ledON = false;
      digitalwrite(onboardLED, LOW);
    }
    else {
      ledON = true;
      digitalwrite(onboardLED, HIGH);
    }
  }
}
