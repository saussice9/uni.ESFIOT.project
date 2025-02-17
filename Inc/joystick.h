// JOYSTICK HEADER FILE

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include <pitches.h>
#include "motor.h"
#include "LED_strip.h"
#include "buzzer.h"
#include "utils.h"

//=============================================================================
//                                   MACROS
//=============================================================================

// #define DEBUG_JOYSTICK  // Uncomment to enable joystick debug messages

// Joystick sensitivity arbitrary quantum
#define SENSITIVITY_EPSILON 50

// Default position of X and Y when the joystick is untouched
#define DEFAULT_POSITION 520
#define MAX_POSITION 1023
#define MIN_POSITION 0
#define MAX_10BITS 1023

// Joystick switch
#define SW 3

//=============================================================================
//                             VARIABLE DECLARATIONS
//=============================================================================

extern unsigned long lastDebounceTime;
extern unsigned long debounceDelay;
extern int lastButtonState;
extern int buttonState;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

extern void readJoystick();
extern void readJoystickSwitch();
