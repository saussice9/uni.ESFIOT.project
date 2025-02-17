// JOYSTICK SOURCE FILE 

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/joystick.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = HIGH;
int buttonState;

//=============================================================================
//                             ROUTINE DEFINITIONS
//=============================================================================


// This procedure reads the joystick values and updates the LED mode and the motors settings (speed,direction) accordingly
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
  
  // This procedure handles the joystick switch and updates the LED pattern accordingly
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
  