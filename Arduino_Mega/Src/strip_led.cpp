/**
* @file strip_led.cpp
* @brief Source file for the LED strip functionality.
* 
* This file contains the implementation of the LED strip control functions, including
* the definition of LED display patterns and the routines to update the LED display.
*/

#pragma once

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/strip_led.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

/**
* @brief RGB color values for default pattern.
*/
const uint RGB_values1[n_LED1][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 0, 50, 50 }, { 69, 6, 23 } }; 

/**
* @brief RGB color values for Italy pattern.
*/
const uint RGB_values2[n_LED2][3] = { { 100, 0, 0 }, { 0, 100, 0 }, { 50, 50, 50 } }; 

/**
* @brief RGB color values for France pattern.
*/
const uint RGB_values3[n_LED3][3] = { { 100, 0, 0 }, { 50, 50, 50 }, { 0, 0, 100 } }; 

/**
* @brief RGB color values for rainbow pattern.
*/
const uint RGB_values4[n_LED4][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 5, 50, 30 }, { 0, 100, 0 }, { 50, 40, 0 }, { 75, 15, 0 }, { 100, 0, 0 } }; 

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
int mode = 0;

/**
* @brief NeoPixel strip controller instance.
*/
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800); 


//=============================================================================
//                             ROUTINE DEFINITIONS
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
void updateLED_Display() {

  // Pattern control variable that controls the offset of the LED display pattern.
  static int offset = 0;
  
  pixels.clear();
  
  // For dynamic modes (4-7), add timing control
  if (mode >= 4 && mode <= 7) {
      static unsigned long lastUpdate = 0;
      unsigned long currentTime = millis();
      
      if (currentTime - lastUpdate >= 100) {
          lastUpdate = currentTime;
          offset = (offset + 1) % getPatternSize(mode);
      }
  } else {
      offset = 0;  // Reset offset for static modes
  }
  
  if (mode!=8){

    // Use the same pattern logic for both static and dynamic modes
    int patternMode = mode % 4;  // Maps modes 4-7 to their static counterparts 0-3
    
    switch (patternMode) {
      case 0:  // Default pattern (modes 0 and 4)
          for (int i = 0; i < NUM_PIXELS; i++) {
              pixels.setPixelColor(i, pixels.Color(RGB_values1[(offset + i) % n_LED1][0], 
                                                 RGB_values1[(offset + i) % n_LED1][1], 
                                                 RGB_values1[(offset + i) % n_LED1][2]));
          }
          break;
          
      case 1:  // Italy pattern (modes 1 and 5)
          for (int i = 0; i < NUM_PIXELS; i++) {
              pixels.setPixelColor(i, pixels.Color(RGB_values2[(offset + i) % n_LED2][0], 
                                                 RGB_values2[(offset + i) % n_LED2][1], 
                                                 RGB_values2[(offset + i) % n_LED2][2]));
          }
          break;
          
          case 2:  // France pattern (modes 2 and 6)
          for (int i = 0; i < NUM_PIXELS; i++) {
              pixels.setPixelColor(i, pixels.Color(RGB_values3[(offset + i) % n_LED3][0], 
                                                 RGB_values3[(offset + i) % n_LED3][1], 
                                                 RGB_values3[(offset + i) % n_LED3][2]));
          }
          break;
          
      case 3:  // Rainbow pattern (modes 3 and 7)
          for (int i = 0; i < NUM_PIXELS; i++) {
              pixels.setPixelColor(i, pixels.Color(RGB_values4[(offset + i) % n_LED4][0], 
                                                 RGB_values4[(offset + i) % n_LED4][1], 
                                                 RGB_values4[(offset + i) % n_LED4][2]));
          }
          break;
    }
  }
  
  pixels.show();
}


/**
 * @brief Retrieves the size of the LED pattern based on the current display mode.
 * @param mode The current display mode number.
 * @return The size of the LED pattern for the given mode.
 */
int getPatternSize(int mode) {
  switch (mode % 4) {
      case 0: return n_LED1;
      case 1: return n_LED2;
      case 2: return n_LED3;
      case 3: return n_LED4;
      default: return n_LED1;
  }
}


/**
* @brief Retrieves the name of the current pattern.
* @param mode Current display mode number.
* @return Name of the active pattern.
*/
char* getPatternName(int mode) {
  switch (mode) {
    case 0:
        return "Default static";
    case 1:
        return "Italy static";
    case 2:
        return "France static";
    case 3:
        return "Rainbow static";
    case 4:
        return "Default dynamic";
    case 5:
        return "Italy dynamic";
    case 6:
        return "France dynamic";
    case 7:
        return "Rainbow dynamic";
    case 8:
        return "Rainbow dynamic and faded";
    case 9:
        return " LED strip off";
    default:
        return "Unknown";
  }
}