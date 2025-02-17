// MOTOR SOURCE FILE

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/motor.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

uint8_t motorSpeedR = 0;
uint8_t motorSpeedL = 0;

driveMode_t driveModeR = STOPPED;
driveMode_t driveModeL = STOPPED;

//=============================================================================
//                             ROUTINE DEFINITIONS
//=============================================================================


// This procedure set both the motors to STOPPED state and with a speed of 0
void resetMotorStates() {
  driveModeR = STOPPED;
  driveModeL = STOPPED;
  motorSpeedR = 0;
  motorSpeedL = 0;
}

// This procedure updates the motors speed based on the related global variables
void applyMotorsSpeed() {

  // set PWM value for both motors
  analogWrite(EN_A, motorSpeedR);
  analogWrite(EN_B, motorSpeedL);

#ifdef DEBUG_MOTORS
  debug.printf("Updated motors speed (L,R): ( %d , %d )\n", motorSpeedL, motorSpeedR);
#endif
}

// This procedure updates the drive modes for both motors based on the related global variables
void applyDriveModes() {

  // modify drive mode for the left motor
  switch (driveModeL) {

    case FORWARD:
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      break;

    case BACKWARDS:
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      break;

    case STOPPED:
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
  }

  // modify drive mode for the right motor
  switch (driveModeR) {

    case FORWARD:
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      break;

    case BACKWARDS:
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      break;

    case STOPPED:
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
  }

#ifdef DEBUG_MOTORS
  debug.printf("Updated motors modes (L,R): ( %s , %s )\n", getDirectionName(driveModeL), getDirectionName(driveModeR));
#endif
}

// This procedure updates the settings of both motors (speed,mode) based on the global variables
void applyMotorsSettings() {

  applyDriveModes();
  applyMotorsSpeed();
}

char* getDirectionName(driveMode_t direction) {
  switch (direction) {
    case 0:
      return "STOPPED";
    case 1:
      return "BACKWARDS";
    case 2:
      return "FORWARD";
    default:
      return "WRONG MODE VALUE";
  }
}