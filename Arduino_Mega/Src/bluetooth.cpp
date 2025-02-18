/**
* @file bluetooth.cpp
* @brief Bluetooh functions and declarations.
* @details Contains the definitions for various Bluetooth-related routines and variables.
*/

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

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
bool BT_process(int* scaled_X, int* scaled_Y) {
    
    char BT_Data = BlueT.read();
    
    bool shouldUpdateMotors = true;
    
    switch (BT_Data){
        // First cases : received data from a pad with few possible values.
        case 'A':
            *scaled_X = DEFAULT_POSITION; 
            *scaled_Y = 0;
            break;

        case 'B':
            *scaled_X = DEFAULT_POSITION; 
            *scaled_Y = DEFAULT_POSITION;
            break;

        case 'C':
            *scaled_X = 0; 
            *scaled_Y = DEFAULT_POSITION;
            break;

        case 'D':
            *scaled_X = -DEFAULT_POSITION; 
            *scaled_Y = DEFAULT_POSITION;
            break;

        case 'E':
            *scaled_X = -DEFAULT_POSITION;
            *scaled_Y = 0;
            break;

        case 'F':
            *scaled_X = -DEFAULT_POSITION; 
            *scaled_Y = -DEFAULT_POSITION;
            break;

        case 'G':
            *scaled_X = 0; 
            *scaled_Y = -DEFAULT_POSITION;
            break;

        case 'H':
            *scaled_X = DEFAULT_POSITION; 
            *scaled_Y = -DEFAULT_POSITION;
            break;

        // 'S' stands for stop
        case 'S':
            *scaled_X = 0; 
            *scaled_Y = 0;
            shouldUpdateMotors = false;
            break;

        // 'M' stands for mode
        case 'M':
            updateMode();
            shouldUpdateMotors = false;
            break;

        // '*' is the prefix for Bluetooth data received from a joystick (not a pad)
        case '*':
            #ifdef DEBUG_MOTORS
            debug.printf("* spotted as prefix in BT_process\n");
            #endif

            // '_' is the suffix for Bluetooth data received from a joystick (not a pad)
            String lineData = BlueT.readStringUntil('_');
            Serial.println("Received data : " + lineData);
            
            // Parse received values and then scale it.
            // First multiply by 4 to scale data that are chars and must be converted to int and then shifted to range in [- DEFAULT_POSITION; DEFAULT_POSITION]
            *scaled_X = 4 * parseValue(lineData, 'X') - DEFAULT_POSITION; 
            *scaled_Y = 4 * parseValue(lineData, 'Y') - DEFAULT_POSITION; 
        
            break;
    }
    return shouldUpdateMotors;
}

/**
 * @brief Parses a value from a string of data.
 *
 * @param data The string of data to parse. Its format is expected to be "X<value_X>,Y<value_Y>"
 * @param axis The character representing the axis to parse ('X' or 'Y').
 * @return The parsed value, or 0 if the axis is not found.
 */
int parseValue(String data, char axis) {
    int index = data.indexOf(axis);
    if (index == -1) return 0;
    
    // Start right after the axis character
    int startIndex = index + 1;

    // Find next letter or end of string
    int endIndex = startIndex;
    while (endIndex < data.length() && isDigit(data.charAt(endIndex))) {
        endIndex++;
    }
    
    String valueStr = data.substring(startIndex, endIndex);
    return valueStr.toInt();
}