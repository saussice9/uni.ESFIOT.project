/**
 * @file motor.h
 * @brief Header file containing motor control declarations and configurations
 */

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "utils.h"

//=============================================================================
//                              TYPE DECLARATIONS
//=============================================================================

/**
 * @brief Enumeration for motor drive modes.
 */
typedef enum driveMode_t {
    STOPPED,    /**< Motor is not moving */
    BACKWARDS,  /**< Motor rotating in reverse */
    FORWARD     /**< Motor rotating forward */
} driveMode_t;

//=============================================================================
//                                   MACROS
//=============================================================================

/**
 * @brief Full speed value for the motors.The maximum value for this variable is 255.
 */
#define FULL_SPEED 100

/**
 * @brief Left motor enable pin.
 */
#define EN_B 5

/**
 * @brief Left motor input pin 4.
 */
#define IN_4 6

/**
 * @brief Left motor input pin 3.
 */
#define IN_3 7

/**
 * @brief Right motor input pin 2.
 */
#define IN_2 8

/**
 * @brief Right motor input pin 1.
 */
#define IN_1 9

/**
 * @brief Left motor enable pin.
 */
#define EN_A 10

/**
 * @brief Scaling factor used to map the default position range to the full motor speed range.
 */
#define MOTOR_SCALING_FACTOR ((float)DEFAULT_POSITION / FULL_SPEED)

//=============================================================================
//                             VARIABLE DECLARATIONS
//=============================================================================


/**
 * @brief Left motor speed.
 */
extern uint8_t motorSpeedL;

/**
 * @brief Right motor speed.
 */
extern uint8_t motorSpeedR;

/**
 * @brief Left motor drive mode.
 */
extern driveMode_t driveModeL;

/**
 * @brief Right motor drive mode.
 */
extern driveMode_t driveModeR;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

/**
 * @brief Resets all motor states to default values (switch-off).
 */
void resetMotorStates();

/**
 * @brief Applies current speed settings to both motors.
 */
void applyMotorsSpeed();

/**
 * @brief Applies current drive mode settings to both motors.
 */
void applyDriveModes();

/**
 * @brief Applies all motor configurations at once.
 */
void applyMotorsSettings();

/**
 * @brief Gets string representation of motor direction.
 * @param direction The drive mode to convert.
 * @return Corresponding direction name.
 */
char* getDirectionName(driveMode_t direction);
