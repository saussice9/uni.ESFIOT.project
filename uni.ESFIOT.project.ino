// Project made for an Arduino Uno
// This project is a simple robot that can be controlled by a smartphone via Bluetooth (not effective yet)
// The robot is equipped with a NeoPixel LED strip that can display different colors and patterns, a buzzer and a joystick
// It is also equipped with two DC motors that can be controlled by the board

//=============================================================================
//                       INCLUDE LIBRARIES AND HEADER FILES
//=============================================================================

//------------------------------------------------------------------------------
// UTILS
//------------------------------------------------------------------------------

#include "Inc/utils.h"  

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

#include "Inc/led_strip.h"

//------------------------------------------------------------------------------
// MOTORS
//------------------------------------------------------------------------------

#include "Inc/motor.h"

//------------------------------------------------------------------------------
// BLUETOOTH
//------------------------------------------------------------------------------

#include <SoftwareSerial.h>  // Library needed by the HC05 Bluetooth module

//------------------------------------------------------------------------------
// BUZZER
//------------------------------------------------------------------------------

#include "Inc/buzzer.h"

//------------------------------------------------------------------------------
// JOYSTICK
//------------------------------------------------------------------------------

#include "Inc/joystick.h"

//=============================================================================
//                             SETUP PROCEDURE
//=============================================================================

// This procedure runs once at the beginning
void setup() {
  Serial.begin(9600);  // Serial communication initialization
  
  pinMode(LED_BUILTIN, OUTPUT);  // Setting built-in LED (pin 13) as output
  
  pinMode(BUZZER_PIN, OUTPUT);  // Setting enable buzzer pin motor (pin 2) as output
  
  pinMode(EN_A, OUTPUT);  // Setting enable right motor (pin 10) as output
  pinMode(EN_B, OUTPUT);  // Setting enable left  motor (pin 5) as output
  pinMode(IN_1, OUTPUT);  // Setting left motor (pin 9) as output
  pinMode(IN_2, OUTPUT);  // Setting left motor (pin 8) as output
  pinMode(IN_3, OUTPUT);  // Setting right motor (pin 7) as output
  pinMode(IN_4, OUTPUT);  // Setting right motor (pin 6) as output
  
  pinMode(SW, INPUT_PULLUP);  // Setting joystick switch as pull-up input
  
  analogWrite(EN_A, 0);
  analogWrite(EN_B, 0);
  
  // Switch off motors
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  
  pinMode(PIN_NEOPIXEL, OUTPUT);  // Setting Neopixel pin (pin 4) as output
  digitalWrite(PIN_NEOPIXEL, LOW);
  
  pixels.begin();  // NeoPixel initialization
  
  updateLED_Display();
}

//=============================================================================
//                             MAIN LOOP PROCEDURE
//=============================================================================

// This procedure runs in loop
void loop() {
  // demoOne();
  // demoTwo();
  // demoThree();
  
  readJoystick();
  updateLED_Display();
  buzz();
  
  //  delay(1000); // to make serial output more readable and chill the motors
}
