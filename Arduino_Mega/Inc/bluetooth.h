/**
* @file bluetooth.h
* @brief Header file containing Bluetooh functions and declarations.
* @details Contains the declarations of various Bluetooth-related routines and variables.
*/

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

// Needed to create a Bluetooth communication instance.
#include <SoftwareSerial.h>

#include "joystick.h"

#include "../Inc/utils.h"

//=============================================================================
//                                   MACROS
//=============================================================================

/**
 * @brief Defines the RX digital pin for the Bluetooth module.
 */
#define RX 11

/**
 * @brief Defines the TX digital pin for the Bluetooth module.
 */
#define TX 12

/**
 * @brief Rate the Bluetooth module communicates at.
 */
#define BT_RATE 57600

//=============================================================================
//                              VARIABLE DECLARATIONS
//=============================================================================

/**
* @brief SoftwareSerial instance for the Bluetooth module.
*/
extern SoftwareSerial BlueT;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

/**
 * @brief Processes Bluetooth data and updates the scaled X and Y coordinates accordingly.
 *
 * This function reads data from the Bluetooth module and updates the scaled X and Y coordinates based on the received data or update the current mode. 
 * It supports various commands that can:
 *      - move the coordinates to predefined positions : case where data is sent using a pad with few possible values.
 *      - allow parsing of custom coordinate values : case where data is sent from a joystick via Bluetooth (from a smartphone or not).
 *
 * @param scaled_X Pointer to an integer that will hold the updated scaled X coordinate.
 * @param scaled_Y Pointer to an integer that will hold the updated scaled Y coordinate.
 * @return True if the motors should be updated, false otherwise (case where just the mode is updated).
 */
extern bool BT_process(int* scaled_X, int* scaled_Y);

/**
 * Parses a value from a string of data.
 *
 * @param data The string of data to parse. Its format is expected to be "X<value_X>,Y<value_Y>
 * @param axis The character representing the axis to parse ('X' or 'Y').
 * @return The parsed value, or 0 if the axis is not found.
 */
extern int parseValue(String data, char axis);