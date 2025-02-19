/**
* @file joystick.cpp
* @brief Processes joystick position readings.
* @details Reads analog values from joystick and controls:
*          - Motor speeds and directions
*          - LED patterns
*          - Operating mode
*/

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/joystick.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

/**
* @brief Time interval required between state changes for debouncing.
* @details Defines how long to wait before accepting a button state change.
*/
const unsigned int debounceDelay = 50;

/**
* @brief Represents the current joystick input.
*/
joystickInput_t JOYSTICK_INPUT = NO_JOYSTICK;

//=============================================================================
//                             ROUTINE DEFINITIONS
//=============================================================================

/**
 * @brief Reads and processes joystick input to control motor speeds and directions.
 * @details Reads joystick input from either Bluetooth or hardware sources, scales the input, and computes the appropriate motor drive modes and speeds. 
 * If the joystick input indicates that the motors should be updated, it calls the `computeDriveModesAndSpeeds()` and `applyMotorsSettings()` functions to update the motor states.
 * @see computeDriveModesAndSpeeds(
 * @see applyMotorsSettings()
 */
void readJoystick() {
  
  int scaled_X, scaled_Y;

  bool shouldUpdateMotors = false;
  
  switch (JOYSTICK_INPUT){
    case BLUETOOTH:
        shouldUpdateMotors = BT_process(&scaled_X, &scaled_Y);
        break;

    case HARDWARE:
        readJoystickSwitch();
        readAndScaleHardwareJoystick(&scaled_X, &scaled_Y);
        break;

    case NO_JOYSTICK:
        return; 
  }
  
  if (shouldUpdateMotors){
    
    #ifdef DEBUG_MOTORS
    debug.printf("(scaled_X, scaled_Y) = (%d,%d)\n", scaled_X, scaled_Y);
    #endif
    
    computeDriveModesAndSpeeds(scaled_X, scaled_Y);
    
    applyMotorsSettings();
  }
}

/**
 * @brief Reads and scales the hardware joystick input.
 * @details Reads the X and Y values from the hardware joystick, scales them to the appropriate range, and stores the scaled values in the provided pointers.
 * @param scaled_X Pointer to an integer where the scaled X value will be stored.
 * @param scaled_Y Pointer to an integer where the scaled Y value will be stored.
 */
void readAndScaleHardwareJoystick(int* scaled_X, int* scaled_Y) {
  
  readJoystickSwitch();
  
  int X = analogRead(A0);  
  int Y = analogRead(A1);

  #ifdef DEBUG_JOYSTICK
  debug.printf("(X, Y) = (%d,%d)\n", X, Y);
  #endif
  
  *scaled_X = X - DEFAULT_POSITION;
  *scaled_Y = Y - DEFAULT_POSITION;
}

/**
* @brief Handles joystick button state.
* @details Implements debounce logic and mode switching.
*/
void readJoystickSwitch() {

  // Last time the joystick button state was debounced. Used for timing in the debounce mechanism.
  static unsigned long lastDebounceTime = 0;

  // Previous state of the joystick button. Used to detect changes in button state.
  static int lastButtonState = HIGH;

  // Current debounced state of the joystick button. Represents the validated button state after debouncing.
  static int buttonState;

  // Read the current state of the joystick button.
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
        updateMode();
        note = 0;
      }
    }
  } 
  lastButtonState = SW_value;
}

/**
 * @brief Computes the drive modes and speeds for the left and right motors based on the scaled joystick input.
 * @param scaled_X The scaled X-axis value from the joystick.
 * @param scaled_Y The scaled Y-axis value from the joystick.
 * @details This function resets the motor states, then determines the appropriate drive mode (forward, backward, or stopped) and speed for the left and right motors based on the scaled joystick input. The function uses a series of conditional statements to handle different combinations of X and Y axis values, applying the appropriate scaling and direction logic to compute the motor speeds.
 */
void computeDriveModesAndSpeeds(int scaled_X, int scaled_Y) {
  
  // Reset motor states
  resetMotorStates();
  
  if (scaled_X > DEADZONE_EPSILON) {
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
    if (scaled_X < -DEADZONE_EPSILON) {
      driveModeR = BACKWARDS;
      driveModeL = BACKWARDS;
      
      if (scaled_Y < 0) {
        motorSpeedL = intToUint8_t(- scaled_X / MOTOR_SCALING_FACTOR + (scaled_Y / MOTOR_SCALING_FACTOR) / 2);
      } else {
        motorSpeedR = intToUint8_t(- scaled_X / MOTOR_SCALING_FACTOR - (scaled_Y / MOTOR_SCALING_FACTOR) / 2);
        motorSpeedL = - scaled_X / MOTOR_SCALING_FACTOR;
      }
    } else {
      if (scaled_Y < - DEADZONE_EPSILON) {
        driveModeR = FORWARD;
        driveModeL = BACKWARDS;
        motorSpeedR = - scaled_Y / MOTOR_SCALING_FACTOR;
        motorSpeedL = - scaled_Y / MOTOR_SCALING_FACTOR;
      } else {
        if (scaled_Y > DEADZONE_EPSILON) {
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
}

/**
* @brief Get the name of the specified joystick input.
* @param joystickInput The joystick input to get the name for.
* @return The name of the specified joystick input as a String.
*/
char* getJoystickInputName(){
  switch (JOYSTICK_INPUT) {
    case HARDWARE:
        return "HARDWARE";
    case BLUETOOTH:
        return "BLUETOOTH";
    case NO_JOYSTICK:
        return "NO_JOYSTICK";
    default:
        return "Unknown";
  }
}