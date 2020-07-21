#include <REncoder.h>

#define PIN_A 12 //GPIO12 (D6 / pin 6)
#define PIN_B 14 //GPIO14 (D5 / pin 5)
#define BUTTON 13 //GPIO13 (D7 / pin 7)

/** 
 * The REncoderConfig.h file contains the configuration parameters.
 * For this example, the RENCODER_ENABLE_SWITCH parameter must be 
 * enabled, otherwise the switch will not work.
 *
 * This example does use IRQs, for both, the encoder and the switch. 
 * Please make sure that the both, the RENCODER_ENABLE_SWITCH_IRQ 
 * and the RENCODER_ENABLE_ENCODER_IRQ parameters are defined/enabled 
 * in the REncoderConfig.h file.
 *
 * Software debouncing is NOT available when IRQs are active.
 *
 * For a simple hardware debouncing, please use 0.1uF/100nF capacitors 
 * between the CLK pin and the GND pin, between the the DT and the GND pins,
 * as well as between the SW and GND pins. This has also the benefice of 
 * freeing up a little bit of MCU's RAM/FLASH resources.
 */

REncoder rEncoder(PIN_A, PIN_B, BUTTON);

void setup() {
  Serial.begin(115200);

  rEncoder.setMinEncoderPosition(-2);
  rEncoder.setMaxEncoderPosition(3);
  
  rEncoder.attachSwitchHandler([]() {
    Serial.println("IRQ -> Switch pushed.");
  });
  
  rEncoder.attachEncoderHandler(
    [](REncoderWithoutSwitch::Event encoderEvent, int16_t encPos) {
    switch (encoderEvent) {
      case REncoder::Event::REncoder_Event_Rotate_CW: 
        Serial.println("IRQ -> Rotation CW to: " + String(encPos));
      break;

      case REncoder::Event::REncoder_Event_Rotate_CCW: 
        Serial.println("IRQ -> Rotation CCW to: " + String(encPos));
      break;
    }
  });
  
}

void loop() {
  
}
