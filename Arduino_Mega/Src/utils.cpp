/**
* @file utils.cpp
* @brief Utility functions and common declarations
* @details This file contains debug utilities and shared functionality for the application.
*/

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/utils.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

/**
* @brief Debug printf instance.
*/
Bonezegei_Printf debug(&Serial); 

//=============================================================================
//                              ROUTINE DEFINITIONS
//=============================================================================

/**
* @brief Increments the current LED and buzzer mode. Mode values range from 0 to 8.
*/
void updateMode() {
    mode = (mode > 7) ? 0 : mode + 1;
}

/**
* @brief Converts the parameter to a unsigned 8-bit integer.
* @param i Input integer value.
* @return Converted unsigned 8-bit integer value.
*/
uint8_t intToUint8_t(int i) {
    if (i > 255) {
        return 255;
    } else {
        if (i < 0) {
            return 0;
        } else {
            return i;
        }
    }
}
