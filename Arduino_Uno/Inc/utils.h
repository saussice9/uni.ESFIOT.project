/**
* @file utils.h
* @brief Header file containing utility functions and common declarations
* @details Contains debug utilities and shared functionality
*/

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include <Bonezegei_Printf.h>

#include "motor.h"
#include "strip_led.h"


//=============================================================================
//                                   MACROS
//=============================================================================

/**
 * @brief Rate the serial port communicates at.
 */
#define SERIAL_RATE 38400


/**
 * @brief Enables debugging output for the motor control.
 */
#define DEBUG_MOTORS


/**
* @brief Enables debugging for the LED strip.
* This macro can be uncommented to enable additional debugging output related to the LED strip.
*/
// #define DEBUG_STRIP_LED


/**
 * @brief Enables debugging output for the joystick.
 * This macro can be uncommented to enable additional logging and debugging information related to the joystick operations.
 */
// #define DEBUG_JOYSTICK

/**
 * @brief Enables debugging output for Bluetooth.
 * This macro can be uncommented to enable additional logging and debugging information related to Bluetooth operations.
 */
#define DEBUG_BT


//=============================================================================
//                              VARIABLE DECLARATIONS
//=============================================================================

/**
* @brief Debug printf instance.
*/
extern Bonezegei_Printf debug;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

/**
* @brief Demonstration routine one.
*/
extern void demoOne();

/**
* @brief Demonstration routine two.
*/
extern void demoTwo();

/**
* @brief Demonstration routine three.
*/
extern void demoThree();

/**
* @brief Changes the current mode.
*/
extern void updateMode();

/**
* @brief Converts integer to uint8_t.
* @param integer_value Input integer value.
* @return Converted uint8_t value.
*/
extern uint8_t intToUint8_t(int integer_value);

/**
* @brief Blinks the built-in LED.
*/
extern void blinkBuiltInLed();