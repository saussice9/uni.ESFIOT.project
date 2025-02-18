/**
* @file utils.h
* @brief Header file containing utility functions and common declarations
* @details Contains debug utilities and shared functionality for the application.
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
 * This macro can be uncommented to enable additional debugging output related to the motors.
 */
#define DEBUG_MOTORS


/**
* @brief Enables debugging output for the LED strip.
* This macro can be uncommented to enable additional debugging output related to the LED strip.
*/
// #define DEBUG_STRIP_LED


/**
 * @brief Enables debugging output for the joystick.
 * This macro can be uncommented to enable additional debugging output related to joystick operations.
 */
#define DEBUG_JOYSTICK

/**
 * @brief Enables debugging output for Bluetooth.
 * This macro can be uncommented to enable additional debugging output related to Bluetooth operations.
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
* @brief Changes the current LED and buzzer mode. Mode values range from 0 to 8.
*/
extern void updateMode();

/**
* @brief Converts the parameter to a unsigned 8-bit integer.
* @param i Input integer value.
* @return Converted unsigned 8-bit integer value.
*/
extern uint8_t intToUint8_t(int integer_value);