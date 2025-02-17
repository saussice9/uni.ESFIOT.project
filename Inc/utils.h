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


//=============================================================================
//                                   MACROS
//=============================================================================

/**
 * @brief Rate the serial port communicates at.
 */
#define SERIAL_RATE 9600

//=============================================================================
//                              VARIABLE DECLARATIONS
//=============================================================================

/**
* @brief Debug printf instance.
*/
extern Bonezegei_Printf debug;

/**
* @brief Current operating mode for LED and buzzer.
*/
extern int mode;

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