/**
 * @file led_strip.cpp
 * @brief Source file for the LED strip functionality.
 * 
 * This file contains the implementation of the LED strip control functions, including
 * the definition of LED display patterns and the routine to update the LED display.
 */

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/led_strip.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

/**
* @brief RGB color values for default pattern
*/
uint RGB_values1[n_LED1][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 0, 50, 50 }, { 69, 6, 23 } };  // default display for the NeoPixels

/**
* @brief RGB color values for Italy pattern
*/
uint RGB_values2[n_LED2][3] = { { 100, 0, 0 }, { 0, 100, 0 }, { 50, 50, 50 } };  // Italy display

/**
* @brief RGB color values for France pattern
*/
uint RGB_values3[n_LED3][3] = { { 100, 0, 0 }, { 50, 50, 50 }, { 0, 0, 100 } };  // France display

/**
* @brief RGB color values for rainbow pattern
*/
uint RGB_values4[n_LED4][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 5, 50, 30 }, { 0, 100, 0 }, { 50, 40, 0 }, { 75, 15, 0 }, { 100, 0, 0 } };  // rainbow display

/**
* @brief Pattern control variable that controls the shift or offset of the LED display pattern.
*/
int shift = 0;

/**
* @brief Variable that tracks the number of LEDs that are the same color in the current display pattern.
*/
int n_same = 0;  // test purpose only

/**
* @brief NeoPixel strip controller instance
*/
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800); 


//=============================================================================
//                             ROUTINE DEFINITIONS
//=============================================================================

/**
* @brief Updates the LED strip display pattern.
*/
void updateLED_Display() {
  
  pixels.clear();  // Switch off all the pixels
  
  switch (mode) {  
    
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    
    case 0:
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(RGB_values1[(shift + i) % n_LED1][0], RGB_values1[(shift + i) % n_LED1][1], RGB_values1[(shift + i) % n_LED1][2]));
    }
    break;
    
    case 1:
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(RGB_values2[(shift + i) % n_LED2][0], RGB_values2[(shift + i) % n_LED2][1], RGB_values2[(shift + i) % n_LED2][2]));
    }
    break;
    
    case 2:
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(RGB_values3[(shift + i) % n_LED3][0], RGB_values3[(shift + i) % n_LED3][1], RGB_values3[(shift + i) % n_LED3][2]));
    }
    break;
    
    case 3: 
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(RGB_values4[(shift + i) % n_LED4][0], RGB_values4[(shift + i) % n_LED4][1], RGB_values4[(shift + i) % n_LED4][2]));
    }
    break;

    case 4:
    if (shift >= n_LED1 - 1) { // default dynamic
      shift = 0;
    } else {
      shift++;
    }
    
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(RGB_values1[(shift + i) % n_LED1][0], RGB_values1[(shift + i) % n_LED1][1], RGB_values1[(shift + i) % n_LED1][2]));
    }
    break;
    
    case 5:
    if (shift >= n_LED2 - 1) { // Italy dynamic
      shift = 0;
    } else {
      shift++;
    }
    
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(RGB_values2[(shift + i) % n_LED2][0], RGB_values2[(shift + i) % n_LED2][1], RGB_values2[(shift + i) % n_LED2][2]));
    }
    break;

    case 6:
    if (shift >= n_LED3 - 1) { // France dynamic
      shift = 0;
    } else {
      shift++;
    }
    
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(RGB_values3[(shift + i) % n_LED3][0], RGB_values3[(shift + i) % n_LED3][1], RGB_values3[(shift + i) % n_LED3][2]));
    }
    break;
    
    case 7: 
    if (shift >= n_LED4 - 1) { // rainbow dynamic
      shift = 0;
    } else {
      shift++;
    }
    
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(RGB_values4[(shift + i) % n_LED4][0], RGB_values4[(shift + i) % n_LED4][1], RGB_values4[(shift + i) % n_LED4][2]));
    }
    break;
    
    case 8:
    if (n_same >= 4) {
      if (shift <= 0) {
        shift = n_LED4 - 1;
      } else {
        shift--;
      }
      n_same = 0;
    } else {
      n_same++;
      for (int i = 0; i < n_same; i++) {  // the first pixels
        pixels.setPixelColor(i, pixels.Color(RGB_values4[(shift - 1) % n_LED4][0], RGB_values4[(shift - 1) % n_LED4][1], RGB_values4[(shift - 1) % n_LED4][2]));
      }
    }
    
    for (int i = 0; i < NUM_PIXELS - 1 / 4; i++) {  // For each pixel...
      
      pixels.setPixelColor(i * 4 + n_same, pixels.Color(RGB_values4[(shift + i) % n_LED4][0], RGB_values4[(shift + i) % n_LED4][1], RGB_values4[(shift + i) % n_LED4][2]));
      pixels.setPixelColor((i * 4 + 1 + n_same) % NUM_PIXELS, pixels.Color(RGB_values4[(shift + i) % n_LED4][0], RGB_values4[(shift + i) % n_LED4][1], RGB_values4[(shift + i) % n_LED4][2]));
      pixels.setPixelColor((i * 4 + 2 + n_same) % NUM_PIXELS, pixels.Color(RGB_values4[(shift + i) % n_LED4][0], RGB_values4[(shift + i) % n_LED4][1], RGB_values4[(shift + i) % n_LED4][2]));
      pixels.setPixelColor((i * 4 + 3 + n_same) % NUM_PIXELS, pixels.Color(RGB_values4[(shift + i) % n_LED4][0], RGB_values4[(shift + i) % n_LED4][1], RGB_values4[(shift + i) % n_LED4][2]));
    }
    break;
    
    #ifdef DEBUG_STRIP_LED
    debug.printf("WRONG MODE VALUE ! \n");
    #endif
  }
  
  #ifdef DEBUG_STRIP_LED
  debug.printf("Current LED display: %s (pattern %d)\n", getPatternName(mode), mode);
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
    return "WRONG MODE VALUE";
  }
}