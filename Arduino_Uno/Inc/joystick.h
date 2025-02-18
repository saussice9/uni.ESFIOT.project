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
#include "strip_LED.h"
#include "buzzer.h"
#include "utils.h"

//=============================================================================
//                                   MACROS
//=============================================================================

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
 * @brief Read BT received joystick position and process the data.
 * @param BT_DATA The Bluetooth data to be processed.
 */
/**
 * @brief Read joystick output, from Bluetooth or from the physical joystick, and process the data.
 * @param use_BT Indicates whether to use Bluetooth data or not.
 * @param BT_DATA The Bluetooth data to be processed.
 */
extern void readJoystick(bool use_BT, char BT_Data);

/**
* @brief Read the joystick switch state and update the LED pattern accordingly.
*/
extern void readJoystickSwitch(); 