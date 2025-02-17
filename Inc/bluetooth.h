/**
* @file bluetooth.h
* @brief Header file containing Bluetooh functions and declarations
* @details Contains the declarations of various Bluetooth-related functions and variables.
*/

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include <SoftwareSerial.h>

//=============================================================================
//                                   MACROS
//=============================================================================

/**
 * @brief Enables debugging output for Bluetooth.
 */
// #define DEBUG_BLUETOOTH

/**
 * @brief Defines the RX pin for the Bluetooth module.
 */
#define RX 11

/**
 * @brief Defines the TX pin for the Bluetooth module.
 */
#define TX 12

/**
 * @brief Rate the Bluetooth module communicates at.
 */
#define BT_RATE 38400

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
 * @brief Processes incoming Bluetooth data.
 * 
 * This function reads data from the Bluetooth module and checks if the received
 * character is 'M'. If so, it calls the `updateMode()` function.
 *
 * TODO: edit this comment accordingly
 */

void BT_process();