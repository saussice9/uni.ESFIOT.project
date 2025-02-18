/**
* @file strip_led.h
* @brief Header file containing LED strip declarations and configurations.
*/

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

/**
 * @brief Includes the Adafruit_NeoPixel library for controlling LED strips.
 * 
 * This header file includes the Adafruit_NeoPixel library, which provides a convenient
 * interface for controlling addressable LED strips, such as NeoPixels.
 */
#include <Adafruit_NeoPixel.h>

/**
 * @brief Conditionally include the AVR power management header file.
 * 
 * This preprocessor directive checks if the code is being compiled for an AVR
 * microcontroller and includes the necessary header file for AVR power management if so.
 */
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "utils.h"

//=============================================================================
//                              TYPE DECLARATIONS
//=============================================================================

/**
* @brief Type alias for unsigned integers.
*/
typedef unsigned int uint;

//=============================================================================
//                                   MACROS
//=============================================================================

/**
* @brief Strip LED data digital pin.
*/
#define PIN_NEOPIXEL 4

/**
* @brief The number of LED in the strip.
*/
#define NUM_PIXELS 64

/**
* @brief Number of LED in the default pattern.
*/
#define n_LED1 4  

/**
* @brief Number of LED in the Italy pattern.
*/
#define n_LED2 3

/**
* @brief Number of LED in the France pattern.
*/
#define n_LED3 3  

/**
* @brief Number of LED in the rainbow pattern.
*/
#define n_LED4 7

//=============================================================================
//                            VARIABLE DECLARATIONS
//=============================================================================

/**
* @brief RGB color values for default pattern.
*/
extern const uint RGB_values1[n_LED1][3]; 

/**
* @brief RGB color values for Italy pattern.
*/
extern const uint RGB_values2[n_LED2][3];

/**
* @brief RGB color values for France pattern.
*/
extern const uint RGB_values3[n_LED3][3];

/**
* @brief RGB color values for rainbow pattern.
*/
extern const uint RGB_values4[n_LED4][3];

/**
* @brief Pattern control variable that controls the offset of the LED display pattern.
*/
extern int offset;  

/**
* @brief Variable that tracks the number of LEDs that are the same color in the current display pattern (pattern 8 only).
*/
extern int n_same; 

/**
* @brief Current operating mode for LED and buzzer.
* @details Here are the possible patterns for LED and buzzer patterns:
*   - 0: Default static, Pink Panther theme
*   - 1: Italy static, Nokia ringtone
*   - 2: France static, Subway Surfers theme
*   - 3: Rainbow static, The Simpsons theme
*   - 4: Default dynamic, Pink Panther theme
*   - 5: Italy dynamic, Nokia ringtone
*   - 6: France dynamic, Subway Surfers theme
*   - 7: Rainbow dynamic, The Simpsons theme
*   - 8: Rainbow dynamic and faded
*  
*/
extern int mode;

/**
* @brief NeoPixel strip controller instance.
*/
extern Adafruit_NeoPixel pixels;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

/**
* @brief Updates the strip LED displayed pattern.
*/
extern void updateLED_Display();

/**
* @brief Retrieves the name of the current pattern.
* @param mode Current display mode number.
* @return Name of the active pattern.
*/
extern char* getPatternName(int mode);