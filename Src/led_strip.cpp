// LED STRIP SOURCE FILE

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/led_strip.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

uint colors[n_color][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 0, 50, 50 }, { 69, 6, 23 } };  // default display for the NeoPixels
uint colors2[n_color2][3] = { { 100, 0, 0 }, { 0, 100, 0 }, { 50, 50, 50 } };  // Italy display
uint colors3[n_color3][3] = { { 100, 0, 0 }, { 50, 50, 50 }, { 0, 0, 100 } };  // France display
uint colors4[n_color4][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 5, 50, 30 }, { 0, 100, 0 }, { 50, 40, 0 }, { 75, 15, 0 }, { 100, 0, 0 } };  // rainbow display

int shift = 0;
int n_same = 0;  // test purpose only

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);  // Setting NeoPixels configuration


//=============================================================================
//                             ROUTINE DEFINITIONS
//=============================================================================

// This procedure updates the LED display based on the current mode
void updateLED_Display() {
  
  pixels.clear();  // Switch off all the pixels
  
  switch (mode) {  // LED display pattern
    
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    
    case 0:
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(colors[(shift + i) % n_color][0], colors[(shift + i) % n_color][1], colors[(shift + i) % n_color][2]));
    }
    break;
    
    case 1:
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(colors2[(shift + i) % n_color2][0], colors2[(shift + i) % n_color2][1], colors2[(shift + i) % n_color2][2]));
    }
    break;
    
    case 2:
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(colors3[(shift + i) % n_color3][0], colors3[(shift + i) % n_color3][1], colors3[(shift + i) % n_color3][2]));
    }
    break;
    
    case 3: 
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
    }
    break;

    case 4:
    if (shift >= n_color - 1) { // default dynamic
      shift = 0;
    } else {
      shift++;
    }
    
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(colors[(shift + i) % n_color][0], colors[(shift + i) % n_color][1], colors[(shift + i) % n_color][2]));
    }
    break;
    
    case 5:
    if (shift >= n_color2 - 1) { // Italy dynamic
      shift = 0;
    } else {
      shift++;
    }
    
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(colors2[(shift + i) % n_color2][0], colors2[(shift + i) % n_color2][1], colors2[(shift + i) % n_color2][2]));
    }
    break;

    case 6:
    if (shift >= n_color3 - 1) { // France dynamic
      shift = 0;
    } else {
      shift++;
    }
    
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(colors3[(shift + i) % n_color3][0], colors3[(shift + i) % n_color3][1], colors3[(shift + i) % n_color3][2]));
    }
    break;
    
    case 7: 
    if (shift >= n_color4 - 1) { // rainbow dynamic
      shift = 0;
    } else {
      shift++;
    }
    
    for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
      pixels.setPixelColor(i, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
    }
    break;
    
    case 8:
    if (n_same >= 4) {
      if (shift <= 0) {
        shift = n_color4 - 1;
      } else {
        shift--;
      }
      n_same = 0;
    } else {
      n_same++;
      for (int i = 0; i < n_same; i++) {  // the first pixels
        pixels.setPixelColor(i, pixels.Color(colors4[(shift - 1) % n_color4][0], colors4[(shift - 1) % n_color4][1], colors4[(shift - 1) % n_color4][2]));
      }
    }
    
    for (int i = 0; i < NUM_PIXELS - 1 / 4; i++) {  // For each pixel...
      
      pixels.setPixelColor(i * 4 + n_same, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
      pixels.setPixelColor((i * 4 + 1 + n_same) % NUM_PIXELS, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
      pixels.setPixelColor((i * 4 + 2 + n_same) % NUM_PIXELS, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
      pixels.setPixelColor((i * 4 + 3 + n_same) % NUM_PIXELS, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
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

// This procedure updates the LED mode and prints the new mode
void updateLED_Mode() {
  if (mode > 8) {
    mode = 0;
  } else {
    mode += 1;
  }
  // counter_change_mode = 0;
  #ifdef DEBUG_STRIP_LED
  debug.printf("NEw LED mode: %s (n° %d )\n", getPatternName(mode), mode);
  #endif
}

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