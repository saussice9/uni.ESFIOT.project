/**
* @file led_strip.h
* @brief Header file containing LED strip declarations and configurations
*/

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include "utils.h"

//=============================================================================
//                              TYPE DECLARATIONS
//=============================================================================

/**
* @brief Type alias for unsigned integers
*/
typedef unsigned int uint;

//=============================================================================
//                                   MACROS
//=============================================================================

/**
* @brief Enables debugging for the LED strip.
* This macro can be uncommented to enable additional debugging output related to the LED strip.
*/
// #define DEBUG_STRIP_LED

/**
* @brief Strip LED pin.
*/
#define PIN_NEOPIXEL 4

/**
* @brief The number of LEDs in the strip.
*/
#define NUM_PIXELS 64

/**
* @brief Number of LED in the default pattern
*/
#define n_LED1 4  

/**
* @brief Number of LED in the Italy pattern
*/
#define n_LED2 3

/**
* @brief Number of LED in the France pattern
*/
#define n_LED3 3  

/**
* @brief Number of LED in the rainbow pattern
*/
#define n_LED4 7

//=============================================================================
//                            VARIABLE DECLARATIONS
//=============================================================================

/**
* @brief RGB color values for default pattern
*/
extern uint RGB_values1[n_LED1][3]; 

/**
* @brief RGB color values for Italy pattern
*/
extern uint RGB_values2[n_LED2][3];

/**
* @brief RGB color values for France pattern
*/
extern uint RGB_values3[n_LED3][3];

/**
* @brief RGB color values for rainbow pattern
*/
extern uint RGB_values4[n_LED4][3];

/**
* @brief Pattern control variable that controls the shift or offset of the LED display pattern.
*/
extern int shift;  

/**
* @brief Variable that tracks the number of LEDs that are the same color in the current display pattern.
*/
extern int n_same; 

/**
* @brief NeoPixel strip controller instance
*/
extern Adafruit_NeoPixel pixels;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

/**
* @brief Updates the LED strip display pattern.
*/
extern void updateLED_Display();

/**
* @brief Retrieves the name of the current pattern.
* @param mode Current display mode number.
* @return Name of the active pattern.
*/
extern char* getPatternName(int mode);