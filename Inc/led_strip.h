// LED STRIP HEADER FILE

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include <Adafruit_NeoPixel.h>  // Library needed to control the NeoPixel LED strip
#ifdef __AVR__
#include <avr/power.h>  // Needed for Adafruit Trinket 16 MHz
#endif

#include "utils.h"

//=============================================================================
//                              TYPE DECLARATIONS
//=============================================================================

typedef unsigned int uint;

//=============================================================================
//                                   MACROS
//=============================================================================

// #define DEBUG_STRIP_LED  // Uncomment to enable strip LED debug messages

#define PIN_NEOPIXEL 4  // Data pin for the LED strip
#define NUM_PIXELS 64   // Number of NeoPixels

#define n_color 4
#define n_color2 3
#define n_color3 3
#define n_color4 7

//=============================================================================
//                            VARIABLE DECLARATIONS
//=============================================================================

extern uint colors[n_color][3];  // default display for the NeoPixels
extern uint colors2[n_color2][3];  // Italy display
extern uint colors3[n_color3][3] ;  // France display
extern uint colors4[n_color4][3];  // rainbow display

extern int shift;
extern int n_same;  // test purpose only

extern Adafruit_NeoPixel pixels;  // Setting NeoPixels configuration

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

extern void updateLED_Display();
extern void updateLED_Mode();
extern char* getPatternName(int mode);