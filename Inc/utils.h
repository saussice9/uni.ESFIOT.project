// UTILS HEADER FILE

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include <Bonezegei_Printf.h>
#include "motor.h"

//=============================================================================
//                              VARIABLE DECLARATIONS
//=============================================================================

extern Bonezegei_Printf debug;  // enable printf
extern int mode;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

extern void demoOne(); 
extern void demoTwo(); 
extern void demoThree();
extern uint8_t intToUint8_t(int integer_value);
extern void blinkBuiltInLed();
