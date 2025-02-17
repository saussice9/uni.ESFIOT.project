/**
* @file joystick.cpp
* @brief Processes joystick position readings
* @details Reads analog values from joystick and controls:
*          - Motor speeds and directions
*          - LED patterns
*          - Operating modes
*/

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/joystick.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

/**
* @brief Last time the joystick button state was debounced
* @details Used for timing in the debounce mechanism
*/
unsigned long lastDebounceTime = 0;

/**
* @brief Time interval required between state changes for debouncing
* @details Defines how long to wait before accepting a button state change
*/
unsigned long debounceDelay = 50;

/**
* @brief Previous state of the joystick button
* @details Used to detect changes in button state
*/
int lastButtonState = HIGH;

/**
* @brief Current debounced state of the joystick button
* @details Represents the validated button state after debouncing
*/
int buttonState;

//=============================================================================
//                             ROUTINE DEFINITIONS
//=============================================================================

/**
* @brief Processes joystick position readings
* @details Reads analog values from joystick and controls:
*          - Motor speeds and directions
*          - LED patterns
*          - Operating modes
*/
void readJoystick() {
  readJoystickSwitch();
  
  int X = analogRead(A0);  
  int Y = analogRead(A1);
  #ifdef DEBUG_JOYSTICK
  debug.printf("(X, Y) = (%d,%d)\n", X, Y);
  #endif
  
  // Read joystick values
  int scaled_X = analogRead(A0) - DEFAULT_POSITION;  // scaled_X ∈ [-DEFAULT_POSITION, DEFAULT_POSITION ]
  int scaled_Y = analogRead(A1) - DEFAULT_POSITION;  // scaled_Y ∈ [-DEFAULT_POSITION, DEFAULT_POSITION ]
  
  #ifdef DEBUG_MOTORS
  debug.printf("(scaled_X, scaled_Y) = (%d,%d)\n", scaled_X, scaled_Y);
  #endif
  
  // Reset motor states
  resetMotorStates();
  
  if (scaled_X > SENSITIVITY_EPSILON) {
    driveModeR = FORWARD;
    driveModeL = FORWARD;
    
    if (scaled_Y < 0) {
      motorSpeedR = scaled_X / MOTOR_SCALING_FACTOR;  
      motorSpeedL = intToUint8_t(scaled_X / MOTOR_SCALING_FACTOR + (scaled_Y / MOTOR_SCALING_FACTOR) / 2);
    } else {
      motorSpeedR = intToUint8_t(scaled_X / MOTOR_SCALING_FACTOR - (scaled_Y / MOTOR_SCALING_FACTOR) / 2);
      motorSpeedL = scaled_X  / MOTOR_SCALING_FACTOR;
    }
    
  } else {
    if (scaled_X < -SENSITIVITY_EPSILON) {
      driveModeR = BACKWARDS;
      driveModeL = BACKWARDS;
      
      if (scaled_Y < 0) {
        motorSpeedL = intToUint8_t(- scaled_X / MOTOR_SCALING_FACTOR + (scaled_Y / MOTOR_SCALING_FACTOR) / 2);
      } else {
        motorSpeedR = intToUint8_t(- scaled_X / MOTOR_SCALING_FACTOR - (scaled_Y / MOTOR_SCALING_FACTOR) / 2);
        motorSpeedL = - scaled_X / MOTOR_SCALING_FACTOR;
      }
    } else {
      if (scaled_Y < - SENSITIVITY_EPSILON) {
        driveModeR = FORWARD;
        driveModeL = BACKWARDS;
        motorSpeedR = - scaled_Y / MOTOR_SCALING_FACTOR;
        motorSpeedL = - scaled_Y / MOTOR_SCALING_FACTOR;
      } else {
        if (scaled_Y > SENSITIVITY_EPSILON) {
          driveModeR = BACKWARDS;
          driveModeL = FORWARD;
          motorSpeedR = scaled_Y / MOTOR_SCALING_FACTOR;
          motorSpeedL = scaled_Y / MOTOR_SCALING_FACTOR;
        } else {
          driveModeR = STOPPED;
          driveModeL = STOPPED;
          motorSpeedR = 0;
          motorSpeedL = 0;
        }
      }
    }
  }
  applyMotorsSettings();
  
}

/**
* @brief Handles joystick button state
* @details Implements debounce logic and mode switching
*/

void readJoystickSwitch() {
  int SW_value = digitalRead(SW);
  
  if (SW_value != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (SW_value != buttonState) {
      buttonState = SW_value;
      
      if (buttonState == LOW) {
        #ifdef DEBUG_JOYSTICK || DEBUG_STRIP_LED
        debug.printf("Switch pressed, LED pattern updating... \n");
        #endif
        updateLED_Mode();
        note = 0;
      }
    }
  } 
  lastButtonState = SW_value;
}
