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
*   - 8: LED off
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
 * @brief Updates the LED display based on the current mode.
 * 
 * This function handles the logic for updating the LED display. 
 * It clears the NeoPixel strip, applies timing control for dynamic modes, and then sets the
 * pixel colors based on the current display mode. 
 * The procedure supports four different patterns: default, Italy, France, and rainbow. 
 * It also handles both static and dynamic modes.
 */
extern void updateLED_Display();

/**
 * @brief Retrieves the size of the LED pattern based on the current display mode.
 * @param mode The current display mode number.
 * @return The size of the LED pattern for the given mode.
 */
extern int getPatternSize(int mode);

/**
* @brief Retrieves the name of the current pattern.
* @param mode Current display mode number.
* @return Name of the active pattern.
*/
extern char* getPatternName(int mode);