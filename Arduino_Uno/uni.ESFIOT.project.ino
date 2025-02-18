/**
 * @file uni.ESFIOT.project.ino
 * @brief Main Arduino project file for robot control system
 * @details Robot features:
 *          - Bluetooth control capability
 *          - NeoPixel LED strip with patterns
 *          - Buzzer for audio feedback
 *          - Joystick input
 *          - Dual DC motor control
 */

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

//------------------------------------------------------------------------------
// UTILS
//------------------------------------------------------------------------------

#include "Inc/utils.h"

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

#include "Inc/strip_led.h"

//------------------------------------------------------------------------------
// MOTORS
//------------------------------------------------------------------------------

#include "Inc/motor.h"

//------------------------------------------------------------------------------
// BLUETOOTH
//------------------------------------------------------------------------------

#include "Inc/bluetooth.h"

//------------------------------------------------------------------------------
// BUZZER
//------------------------------------------------------------------------------

#include "Inc/buzzer.h"

//------------------------------------------------------------------------------
// JOYSTICK
//------------------------------------------------------------------------------

#include "Inc/joystick.h"

//=============================================================================
//                             SETUP PROCEDURE
//=============================================================================

/**
 * @brief Initial setup function
 * @details Configures:
 *          - Serial communication
 *          - GPIO pin modes
 *          - Motor initial states
 *          - LED strip initialization
 */
void setup() {
  Serial.begin(SERIAL_RATE);

  // Launch Bluetooth
  BlueT.begin(BT_RATE);

  // Buillt-in LED configuration
  pinMode(LED_BUILTIN, OUTPUT);

  // Buzzer configuration
  pinMode(BUZZER_PIN, OUTPUT);

  // Motor pins configuration
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  pinMode(SW, INPUT_PULLUP);

  // Initial motor states (switched off)
  resetMotorStates();
  applyMotorsSettings();

  // NeoPixel setup
  pinMode(PIN_NEOPIXEL, OUTPUT);
  digitalWrite(PIN_NEOPIXEL, LOW);
  pixels.begin();

  updateLED_Display();
}

//=============================================================================
//                             MAIN LOOP PROCEDURE
//=============================================================================

/**
 * @brief Main program loop
 * @details Continuously:
 *          - Reads joystick input
 *          - Updates LED patterns
 *          - Controls buzzer output
 */
void loop() {

  if (BlueT.available()) BT_process();

  delay(200); // to make serial output more readable and chill the motors

  readJoystick();
  updateLED_Display();
  buzz();
}
