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
const uint RGB_values1[n_LED1][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 0, 50, 50 }, { 69, 6, 23 } };  // default display for the NeoPixels

/**
* @brief RGB color values for Italy pattern.
*/
const uint RGB_values2[n_LED2][3] = { { 100, 0, 0 }, { 0, 100, 0 }, { 50, 50, 50 } };  // Italy display

/**
* @brief RGB color values for France pattern.
*/
const uint RGB_values3[n_LED3][3] = { { 100, 0, 0 }, { 50, 50, 50 }, { 0, 0, 100 } };  // France display

/**
* @brief RGB color values for rainbow pattern.
*/
const uint RGB_values4[n_LED4][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 5, 50, 30 }, { 0, 100, 0 }, { 50, 40, 0 }, { 75, 15, 0 }, { 100, 0, 0 } };  // rainbow display

/**
* @brief Pattern control variable that controls the offset of the LED display pattern.
*/
int offset = 0;

/**
* @brief Tracks the number of LEDs that are the same color in the current display pattern (pattern 8 only).
*/
int n_same = 0; 

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
int mode = 0;

/**
* @brief NeoPixel strip controller instance.
*/
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800); 


//=============================================================================
//                             ROUTINE DEFINITIONS
//=============================================================================

/**
* @brief Updates the strip LED displayed pattern.
*/
void updateLED_Display() {

  // Switch off all the pixels
  pixels.clear();  
  
  switch (mode) {
    
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    
    case 0:
        for (int i = 0; i < NUM_PIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(RGB_values1[(offset + i) % n_LED1][0], RGB_values1[(offset + i) % n_LED1][1], RGB_values1[(offset + i) % n_LED1][2]));
        }
        break;
    
    case 1:
        for (int i = 0; i < NUM_PIXELS; i++) {  
          pixels.setPixelColor(i, pixels.Color(RGB_values2[(offset + i) % n_LED2][0], RGB_values2[(offset + i) % n_LED2][1], RGB_values2[(offset + i) % n_LED2][2]));
        }
        break;
    
    case 2:
        for (int i = 0; i < NUM_PIXELS; i++) { 
          pixels.setPixelColor(i, pixels.Color(RGB_values3[(offset + i) % n_LED3][0], RGB_values3[(offset + i) % n_LED3][1], RGB_values3[(offset + i) % n_LED3][2]));
        }
        break;
    
    case 3: 
        for (int i = 0; i < NUM_PIXELS; i++) { 
          pixels.setPixelColor(i, pixels.Color(RGB_values4[(offset + i) % n_LED4][0], RGB_values4[(offset + i) % n_LED4][1], RGB_values4[(offset + i) % n_LED4][2]));
        }
        break;
    
    case 4:
        if (offset >= n_LED1 - 1) {
          offset = 0;
        } else {
          offset++;
        }
        
        for (int i = 0; i < NUM_PIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(RGB_values1[(offset + i) % n_LED1][0], RGB_values1[(offset + i) % n_LED1][1], RGB_values1[(offset + i) % n_LED1][2]));
        }
        break;
    
    case 5:
        if (offset >= n_LED2 - 1) {
          offset = 0;
        } else {
          offset++;
        }
        
        for (int i = 0; i < NUM_PIXELS; i++) { 
          pixels.setPixelColor(i, pixels.Color(RGB_values2[(offset + i) % n_LED2][0], RGB_values2[(offset + i) % n_LED2][1], RGB_values2[(offset + i) % n_LED2][2]));
        }
        break;
    
    case 6:
        if (offset >= n_LED3 - 1) {
          offset = 0;
        } else {
          offset++;
        }
        
        for (int i = 0; i < NUM_PIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(RGB_values3[(offset + i) % n_LED3][0], RGB_values3[(offset + i) % n_LED3][1], RGB_values3[(offset + i) % n_LED3][2]));
        }
        break;
    
    case 7: 
        if (offset >= n_LED4 - 1) {
          offset = 0;
        } else {
          offset++;
        }
        
        for (int i = 0; i < NUM_PIXELS; i++) { 
          pixels.setPixelColor(i, pixels.Color(RGB_values4[(offset + i) % n_LED4][0], RGB_values4[(offset + i) % n_LED4][1], RGB_values4[(offset + i) % n_LED4][2]));
        }
        break;
    
    case 8:
        if (n_same >= 4) {
          if (offset <= 0) {
            offset = n_LED4 - 1;
          } else {
            offset--;
          }
          n_same = 0;
        } else {
          n_same++;
          for (int i = 0; i < n_same; i++) { 
            pixels.setPixelColor(i, pixels.Color(RGB_values4[(offset - 1) % n_LED4][0], RGB_values4[(offset - 1) % n_LED4][1], RGB_values4[(offset - 1) % n_LED4][2]));
          }
        }
    
        for (int i = 0; i < NUM_PIXELS - 1 / 4; i++) {  
          
          pixels.setPixelColor(i * 4 + n_same, pixels.Color(RGB_values4[(offset + i) % n_LED4][0], RGB_values4[(offset + i) % n_LED4][1], RGB_values4[(offset + i) % n_LED4][2]));
          pixels.setPixelColor((i * 4 + 1 + n_same) % NUM_PIXELS, pixels.Color(RGB_values4[(offset + i) % n_LED4][0], RGB_values4[(offset + i) % n_LED4][1], RGB_values4[(offset + i) % n_LED4][2]));
          pixels.setPixelColor((i * 4 + 2 + n_same) % NUM_PIXELS, pixels.Color(RGB_values4[(offset + i) % n_LED4][0], RGB_values4[(offset + i) % n_LED4][1], RGB_values4[(offset + i) % n_LED4][2]));
          pixels.setPixelColor((i * 4 + 3 + n_same) % NUM_PIXELS, pixels.Color(RGB_values4[(offset + i) % n_LED4][0], RGB_values4[(offset + i) % n_LED4][1], RGB_values4[(offset + i) % n_LED4][2]));
        }
        break;
  }
  
  #ifdef DEBUG_STRIP_LED
  debug.printf("Current LED display: %s (pattern #%d)\n", getPatternName(mode), mode);
  #endif 
  
  pixels.show();
  
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