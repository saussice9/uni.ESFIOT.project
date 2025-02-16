/**
* @file joystick.h
* @brief Header file containing joystick-related declarations and configurations.
*/

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include <pitches.h>
#include "motor.h"
#include "LED_strip.h"
#include "buzzer.h"
#include "utils.h"

//=============================================================================
//                                   MACROS
//=============================================================================

/**
 * @brief Enables debugging output for the joystick.
 * This macro can be uncommented to enable additional logging and debugging information related to the joystick operations.
 */
// #define DEBUG_JOYSTICK


/**
* @brief Deadzone threshold for joystick sensitivity.
*/
#define SENSITIVITY_EPSILON 50  

/**
* @brief The default position for the joystick, which represents the center or neutral position.
*/
#define DEFAULT_POSITION 520 

/**
* @brief The maximum value that can be represented by the joystick position.
*/
#define MAX_POSITION 1023

/**
* @brief The minimum value that can be represented by the joystick position.
*/
#define MIN_POSITION 0  

/**
* @brief Joystick switch pin.
*/
#define SW 3

//=============================================================================
//                             VARIABLE DECLARATIONS
//=============================================================================

/**
 * @brief Last time the joystick button state was debounced.
 */
extern unsigned long lastDebounceTime;

/**
 * @brief Delay time in milliseconds used for debouncing the joystick button.
 */
extern unsigned long debounceDelay;

/**
 * @brief Last state of the joystick button.
 */
extern int lastButtonState;

/**
 * @brief Current state of the joystick button.
 */
extern int buttonState;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

/**
* @brief Read joystick position and process the data.
*/
extern void readJoystick();

/**
* @brief Read the joystick switch state and update the LED pattern accordingly.
*/
extern void readJoystickSwitch(); 