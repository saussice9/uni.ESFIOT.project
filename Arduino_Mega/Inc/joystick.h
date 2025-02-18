/**
* @file joystick.h
* @brief Header file containing joystick-related declarations and configurations.
*/

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "motor.h"

#include "strip_LED.h"

#include "buzzer.h"

#include "bluetooth.h"

#include "utils.h"

//=============================================================================
//                              TYPE DECLARATIONS
//=============================================================================


/**
 * @brief Enumeration representing the different types of joystick input.
 * 
 */
typedef enum joystickInput_t {
    HARDWARE, /**< Use joystick connected to the Arduino board.*/
    BLUETOOTH, /**< Use received Bluetooth joystick input.*/
    NO_JOYSTICK  /**< No joystick input.*/
} joystickInput_t;

//=============================================================================
//                                   MACROS
//=============================================================================

/**
* @brief Deadzone threshold for joystick sensitivity. The higher DEADZONE_EPSILON, the larger the deadzone (i.e., the joystick must be moved further from the center to register a change).
* @details The deadzone is a region around the center position where the joystick is considered to be in a neutral state.
* @note The deadzone is defined as the range between DEFAULT_POSITION - DEADZONE_EPSILON and DEFAULT_POSITION + DEADZONE_EPSILON.
*/
#define DEADZONE_EPSILON 50  

/**
* @brief The default raw position for the joystick, which represents the center or neutral position.
*/
#define DEFAULT_POSITION 512

/**
* @brief The maximum value that can be represented by the joystick position.
*/
#define MAX_POSITION 1023

/**
* @brief Joystick analog switch pin.
*/
#define SW 3

//=============================================================================
//                             VARIABLE DECLARATIONS
//=============================================================================

/**
* @brief Last time the joystick button state was debounced.
* @details Used for timing in the debounce mechanism.
*/
extern unsigned long lastDebounceTime;

/**
* @brief Time interval required between state changes for debouncing.
* @details Defines how long to wait before accepting a button state change.
*/
extern const unsigned long debounceDelay;

/**
* @brief Previous state of the joystick button.
* @details Used to detect changes in button state.
*/
extern int lastButtonState;

/**
* @brief Current debounced state of the joystick button.
* @details Represents the validated button state after debouncing.
*/
extern int buttonState;

/**
 * @brief Represents the current joystick input.
 */
extern joystickInput_t JOYSTICK_INPUT;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

/**
 * @brief Reads and processes joystick input to control motor speeds and directions.
 * @details Reads joystick input from either Bluetooth or hardware sources, scales the input, and computes the appropriate motor drive modes and speeds. 
 * If the joystick input indicates that the motors should be updated, it calls the `computeDriveModesAndSpeeds()` and `applyMotorsSettings()` functions to update the motor states.
 * @see computeDriveModesAndSpeeds(
 * @see applyMotorsSettings()
 */
extern void readJoystick();

/**
 * @brief Reads and scales the hardware joystick input.
 * @details Reads the X and Y values from the hardware joystick, scales them to the appropriate range, and stores the scaled values in the provided pointers.
 * @param scaled_X Pointer to an integer where the scaled X value will be stored.
 * @param scaled_Y Pointer to an integer where the scaled Y value will be stored.
 */
extern void readAndScaleHardwareJoystick(int* scaled_X, int* scaled_Y);


/**
* @brief Handles joystick button state.
* @details Implements debounce logic and mode switching.
*/
extern void readJoystickSwitch(); 

/**
 * @brief Computes the drive modes and speeds for the left and right motors based on the scaled joystick input.
 * @param scaled_X The scaled X-axis value from the joystick.
 * @param scaled_Y The scaled Y-axis value from the joystick.
 * @details This function resets the motor states, then determines the appropriate drive mode (forward, backward, or stopped) and speed for the left and right motors based on the scaled joystick input. The function uses a series of conditional statements to handle different combinations of X and Y axis values, applying the appropriate scaling and direction logic to compute the motor speeds.
 */
extern void computeDriveModesAndSpeeds(int scaled_X, int scaled_Y);


/**
 * @brief Get the name of the specified joystick input.
 * @param joystickInput The joystick input to get the name for.
 * @return The name of the specified joystick input as a String.
 */
extern char* getJoystickInputName();

