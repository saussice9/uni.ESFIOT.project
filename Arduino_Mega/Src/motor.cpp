/**
* @file motor.cpp
* @brief Provides implementation for motor control functionality.
*
* This file contains the definitions for motor-related routines and variables.
* It handles the low-level control of the motors, including setting the speed and drive mode for both motors.
*/

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/motor.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

/**
* @brief Left motor PWM speed. Must be between 0 and 255.
* Limited by 
*/
uint8_t motorSpeedL = 0;

/**
* @brief Right motor PWM speed. Must be between 0 and 255.
*/
uint8_t motorSpeedR = 0;

/**
* @brief Left motor drive mode.
*/
driveMode_t driveModeL = STOPPED;

/**
* @brief Right motor drive mode.
*/
driveMode_t driveModeR = STOPPED;

//=============================================================================
//                             ROUTINE DEFINITIONS
//=============================================================================


/**
* @brief Resets both motor states to default values (switched-off).
*/
void resetMotorStates() {
  driveModeR = STOPPED;
  driveModeL = STOPPED;
  motorSpeedR = 0;
  motorSpeedL = 0;
}

/**
* @brief Applies current speed settings to both motors.
*/
void applyMotorsSpeed() {
  
  // set PWM value for both motors
  analogWrite(EN_A, motorSpeedR);
  analogWrite(EN_B, motorSpeedL);
  
  #ifdef DEBUG_MOTORS
  debug.printf("Updated motors speed (L,R): ( %d , %d )\n", motorSpeedL, motorSpeedR);
  #endif
}

/**
* @brief Applies current drive mode settings to both motors.
*/
void applyDriveModes() {
  
  // modify drive mode for the left motor
  switch (driveModeL) {
    
    case FORWARD:
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, HIGH);
        break;
    
    case BACKWARDS:
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
        break;
    
    case STOPPED:
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
  }
  
  // modify drive mode for the right motor
  switch (driveModeR) {
    
    case FORWARD:
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, HIGH);
        break;
    
    case BACKWARDS:
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);
        break;
    
    case STOPPED:
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
  }
  
  #ifdef DEBUG_MOTORS
  debug.printf("Updated motors modes (L,R): ( %s , %s )\n", getDirectionName(driveModeL), getDirectionName(driveModeR));
  #endif
}

/**
* @brief Applies all motor configurations at once.
*/
void applyMotorsSettings() {
  
  applyDriveModes();
  applyMotorsSpeed();
}

/**
* @brief Gets string representation of motor direction.
* @param direction The drive mode to convert.
* @return Corresponding direction name.
*/
char* getDirectionName(driveMode_t direction) {
  switch (direction) {
    case 0:
        return "STOPPED";
    case 1:
        return "BACKWARDS";
    case 2:
        return "FORWARD";
    default:
        return "WRONG MODE VALUE";
  }
}