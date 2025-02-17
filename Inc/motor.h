// MOTOR HEADER FILE

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "utils.h"

//=============================================================================
//                              TYPE DECLARATIONS
//=============================================================================

typedef enum driveMode_t {
    STOPPED,
    BACKWARDS,
    FORWARD
  } driveMode_t;

//=============================================================================
//                                   MACROS
//=============================================================================

// #define DEBUG_MOTORS  // Uncomment to enable motors debug messages

#define FULL_SPEED 100

// Left motor
#define EN_B 5
#define IN_4 6
#define IN_3 7

// Right motor
#define IN_2 8
#define IN_1 9
#define EN_A 10

#define MOTOR_SCALING_FACTOR ((float)DEFAULT_POSITION / FULL_SPEED)

//=============================================================================
//                             VARIABLE DECLARATIONS
//=============================================================================

extern uint8_t motorSpeedR;
extern uint8_t motorSpeedL;

extern driveMode_t driveModeR;
extern driveMode_t driveModeL;


//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

void resetMotorStates();
void applyMotorsSpeed();
void applyDriveModes();
void applyMotorsSettings();
char* getDirectionName(driveMode_t direction);
