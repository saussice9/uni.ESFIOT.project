/**
* @file Arduino_Mega.ino
* @brief Main Arduino project file for robot control system.
* @details Robot features:
*          - Bluetooth control capability (using another board or a smartphone)
*          - NeoPixel LED strip with 8 patterns
*          - Buzzer for music
*          - Analog joystick handling for motor control
*          - Dual DC motor speed and direction control
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
 * @brief Initializes the Arduino Mega board and sets up the various peripherals.
 * @details This function is called once at the start of the program. It performs the following tasks:
 *          - Initializes the serial communication at the specified baud rate.
 *          - Starts the Bluetooth communication at the specified baud rate.
 *          - Configures multiple pins (strip LED, buzzer, motors ...).
 *          - Switch off the motors.
 *          - Initialize the strip LED.
 */

/**
 * @brief Initializes the Arduino Mega board and sets up the various peripherals.
 * @details This function is called once at the start of the program. It performs the following tasks:
 *          - Initializes the serial communication at the specified baud rate.
 *          - Starts the Bluetooth communication at the specified baud rate.
 *          - Configures multiple pins (buzzer, motors, NeoPixel).
 *          - Switches off the motors.
 *          - Initializes the NeoPixel strip.
 *          - Calls the `updateLED_Display()` function to update the LED display.
 */
void setup() {

  // Launch serial communication
  Serial.begin(SERIAL_RATE);

  // Launch Bluetooth
  BlueT.begin(BT_RATE);

  // Buzzer configuration
  pinMode(BUZZER_PIN, OUTPUT);

  // Motor pins configuration
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  // Harwdare joystick switch pin configuration
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
 * @brief The main loop of the Arduino Mega program.
 * @details This function is called repeatedly after the `setup()` function. It performs the following tasks:
 *          - Determines the current joystick input mode ('Bluetooth' or 'no joystick').
 *          - Reads the joystick input.
 *          - Updates the LED display.
 *          - Play buzzer music.
 */
void loop() {

  JOYSTICK_INPUT = BlueT.available() ? BLUETOOTH : NO_JOYSTICK;

  // delay(200); // to make serial output more readable and chill the motors if needed

#ifdef DEBUG_JOYSTICK
  debug.printf("Input mode: %s\n", getJoystickInputName());
#endif

  readJoystick();

  updateLED_Display();

  buzz();
}
