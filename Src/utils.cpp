// UTILS SOURCE FILE 

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

#include "../Inc/utils.h"

//=============================================================================
//                             VARIABLE DEFINITIONS
//=============================================================================

Bonezegei_Printf debug(&Serial);  // enable printf
int mode = 0;

//=============================================================================
//                              ROUTINE DEFINITIONS
//=============================================================================

// This example lets the motors run in both directions at a constant speed
void demoOne() {
    
    // Switch on motor A
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    
    // Set motor A speed to 200 on the possible range [0;FULL_SPEED]
    analogWrite(EN_A, 200);
    
    // Switch on motor B
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);
    
    // Set motor B speed to 200 on the possible range [0;FULL_SPEED]
    analogWrite(EN_B, 200);
    delay(2000);
    
    // Change motor A direction
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    
    // Change motor B direction
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    delay(2000);
    
    // Switch off motors
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
}

// This example lets the motors run in both directions at an increasing speed then a decreasing speed
void demoTwo() {
    
    // Note that the max speed is related to the motor itself and the its voltage supply
    // The PWM values sent using analogWrite() are fractions of the theorical max speed
    
    // Switch on motors
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    
    // Speed up from zero to max speed
    for (int i = 0; i < 256; i++) {
        analogWrite(EN_A, i);
        analogWrite(EN_B, i);
        delay(20);
    }
    
    // Slow down from max speed to zero
    for (int i = FULL_SPEED; i >= 0; i--) {
        analogWrite(EN_A, i);
        analogWrite(EN_B, i);
        delay(20);
    }
    
    // switch off motors
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
}


// This example lets the motors run in both directions at a full speed for 2 seconds each
void demoThree() {
    
    analogWrite(EN_A, FULL_SPEED);
    analogWrite(EN_B, FULL_SPEED);
    
    // Switch on motors
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    
    delay(2000);
    
    // switch off motors
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, LOW);
    
    delay(2000);
}

// This procedure converts an integer value to an uint8_t value
uint8_t intToUint8_t(int integer_value) {
    if (integer_value > 255) {
        return 255;
    } else {
        if (integer_value < 0) {
            return 0;
        } else {
            return integer_value;
        }
    }
}

// This procedure blinks the built-in LED
void blinkBuiltInLed() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }