/**
* @file bluetooth.cpp
* @brief Bluetooh functions and declarations
* @details Contains the definitions for various Bluetooth-related functions and variables.
*/

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/utils.h"
#include "../Inc/bluetooth.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

/**
* @brief SoftwareSerial instance for the Bluetooth module.
*/
SoftwareSerial BlueT(RX, TX);

//=============================================================================
//                              ROUTINE DEFINITIONS
//=============================================================================

/**
 * @brief Processes incoming Bluetooth data.
 * 
 * This function reads data from the Bluetooth module and checks if the received
 * character is 'M'. If so, it calls the `updateMode()` function.
 *
 * TODO: edit this comment accordingly
 */

void BT_process() {
    char BT_Data = BlueT.read();
    if (BT_Data == 'M') {
        updateMode();
    }
}
