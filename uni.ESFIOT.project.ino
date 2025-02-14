// Project made for an Arduino Uno
// This project is a simple robot that can be controlled by a smartphone via Bluetooth (not effective yet)
// The robot is equipped with a NeoPixel LED strip that can display different colors and patterns
// The robot is also equipped with two DC motors that can be controlled by the board

//=============================================================================
//                              INCLUDE LIBRARIES
//=============================================================================


//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

#include <Adafruit_NeoPixel.h>  // Library needed to control the NeoPixel LED strip
#ifdef __AVR__
#include <avr/power.h>  // Needed for Adafruit Trinket 16 MHz
#endif


//------------------------------------------------------------------------------
// BLUETOOTH
//------------------------------------------------------------------------------

#include <SoftwareSerial.h>  // Library needed by the HC05 Bluetooth module


//=============================================================================
//                              TYPE DECLARATIONS
//=============================================================================

typedef unsigned int uint;

//------------------------------------------------------------------------------
// MOTORS
//------------------------------------------------------------------------------

typedef enum {
  STOPPED,
  BACKWARDS,
  FORWARD
} motorDirection;

//=============================================================================
//                                   MACROS
//=============================================================================

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

#define PIN_NEOPIXEL 4  // Data pin for the LED strip
#define NUM_PIXELS 64   // Number of NeoPixels

#define n_color 4
uint colors[n_color][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 0, 50, 50 }, { 69, 6, 23 } };  // default display for the NeoPixels
#define n_color2 3
uint colors2[n_color2][3] = { { 100, 0, 0 }, { 0, 100, 0 }, { 50, 50, 50 } };  // Italy display
#define n_color3 3
uint colors3[n_color3][3] = { { 100, 0, 0 }, { 50, 50, 50 }, { 0, 0, 100 } };  // France display
#define n_color4 7
uint colors4[n_color4][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 5, 50, 30 }, { 0, 100, 0 }, { 50, 40, 0 }, { 75, 15, 0 }, { 100, 0, 0 } };  // rainbow display

//------------------------------------------------------------------------------
// MOTORS AND JOYSTICK
//------------------------------------------------------------------------------

// Joystick sensitivity arbitrary quantum
#define SENSITIVITY_EPSILON 150

// Default position of X and Y when the joystick is untouched
#define DEFAULT_POSITION 400
#define MAX_POSITION 780
#define MAX_10BITS 1023

// Left motor
#define EN_B 5
#define IN_4 6
#define IN_3 7

// Right motor
#define IN_2 8
#define IN_1 9
#define EN_A 10

// Joystick switch
#define SW 3

//=============================================================================
//                             GLOBAL VARIABLES
//=============================================================================

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

int shift = 0;
int mode = 2;
// uint counter_change_mode = 0;
int n_same = 0;  // test purpose only

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);  // Setting NeoPixels configuration

//------------------------------------------------------------------------------
// MOTORS AND JOYSTICK
//------------------------------------------------------------------------------

// Motors
uint8_t motorValueR = 0;
uint8_t motorValueL = 0;

motorDirection directionR = STOPPED;
motorDirection directionL = STOPPED;

//Joystick

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = HIGH;
int buttonState;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------
void updateLED_Display();
void updateLED_Mode();

//------------------------------------------------------------------------------
// MOTORS AND JOYSTICK
//------------------------------------------------------------------------------

void demoOne();
void demoTwo();
void demoThree();
void readJoystick();
void readJoystickSwitch();
void controlMotor(uint8_t left_value, uint8_t right_value, motorDirection left_direction, motorDirection right_direction);

//------------------------------------------------------------------------------
// OTHERS
//------------------------------------------------------------------------------
void blinkBuiltInLed();

//=============================================================================
//                             SETUP PROCEDURE
//=============================================================================

// This procedure runs once at the beginning
void setup() {
  Serial.begin(9600);  // Serial communication initialization

  pinMode(LED_BUILTIN, OUTPUT);  // Setting built-in LED (pin 13) as output

  pinMode(EN_A, OUTPUT);  // Setting enable right motor (pin 10) as output
  pinMode(EN_B, OUTPUT);  // Setting enable left  motor (pin 5) as output
  pinMode(IN_1, OUTPUT);  // Setting left motor (pin 9) as output
  pinMode(IN_2, OUTPUT);  // Setting left motor (pin 8) as output
  pinMode(IN_3, OUTPUT);  // Setting right motor (pin 7) as output
  pinMode(IN_4, OUTPUT);  // Setting right motor (pin 6) as output

  pinMode(SW, INPUT_PULLUP);  // Setting joystick switch as pull-up input

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
  // delay(1000);


  readJoystick();
  updateLED_Display();
}

//=============================================================================
//                             PROCEDURE DEFINITIONS
//=============================================================================

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

// This procedure updates the LED display based on the current mode
void updateLED_Display() {
  /* if (counter_change_mode > 50) {
  updateLED_Mode();
  counter_change_mode = 0;
  } else {
  counter_change_mode++;
  } */

  pixels.clear();  // Switch off all the pixels

  switch (mode) {  // LED display mode

    case 0:
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(colors[(shift + i) % n_color][0], colors[(shift + i) % n_color][1], colors[(shift + i) % n_color][2]));
      }
      break;

    case 1:

      if (shift >= n_color - 1) {
        shift = 0;
      } else {
        shift++;
      }

      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(colors[(shift + i) % n_color][0], colors[(shift + i) % n_color][1], colors[(shift + i) % n_color][2]));
      }
      break;

    case 2:

      Serial.println("LED mode 2");
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(colors2[(shift + i) % n_color2][0], colors2[(shift + i) % n_color2][1], colors2[(shift + i) % n_color2][2]));
      }
      break;

    case 3:

      if (shift >= n_color2 - 1) {
        shift = 0;
      } else {
        shift++;
      }

      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(colors2[(shift + i) % n_color2][0], colors2[(shift + i) % n_color2][1], colors2[(shift + i) % n_color2][2]));
      }
      break;

    case 4:
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(colors3[(shift + i) % n_color3][0], colors3[(shift + i) % n_color3][1], colors3[(shift + i) % n_color3][2]));
      }
      break;

    case 5:
      if (shift >= n_color3 - 1) {
        shift = 0;
      } else {
        shift++;
      }

      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(colors3[(shift + i) % n_color3][0], colors3[(shift + i) % n_color3][1], colors3[(shift + i) % n_color3][2]));
      }
      break;

    case 6:
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
      }
      break;

    case 7:

      if (shift >= n_color4 - 1) {
        shift = 0;
      } else {
        shift++;
      }

      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
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

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i * 4 + n_same, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
        pixels.setPixelColor((i * 4 + 1 + n_same) % NUM_PIXELS, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
        pixels.setPixelColor((i * 4 + 2 + n_same) % NUM_PIXELS, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
        pixels.setPixelColor((i * 4 + 3 + n_same) % NUM_PIXELS, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
      }
      break;

    default:
      Serial.println(F("WRONG MODE VALUE"));
  }

  pixels.show();
}

// This procedure updates the LED mode and prints the new mode
void updateLED_Mode() {
  if (mode >= 8) {
    mode = 0;
  } else {
    mode += 1;
  }
  // counter_change_mode = 0;
  Serial.print("Updated LED mode:");
  Serial.println(mode);
}

//------------------------------------------------------------------------------
// MOTORS AND JOYSTICK
//------------------------------------------------------------------------------

// This example lets the motors run in both directions at a constant speed
void demoOne() {

  // Switch on motor A
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  // Set motor A speed to 200 on the possible range [0;255]
  analogWrite(EN_A, 200);

  // Switch on motor B
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  // Set motor B speed to 200 on the possible range [0;255]
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
  for (int i = 255; i >= 0; i--) {
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

  analogWrite(EN_A, 255);
  analogWrite(EN_B, 255);

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


// This procedure reads the joystick values and updates the LED mode and the motors settings (speed,direction) accordingly
void readJoystick() {

  readJoystickSwitch();

  // read the value from the sensor between 0 and 1023:
  int sensorValueY = analogRead(A0);  // variable to store the value coming from the sensor
  int sensorValueX = analogRead(A1);  // variable to store the value coming from the sensor

  Serial.print("Axis values: ");
  Serial.print("X = ");
  Serial.print(sensorValueX);
  Serial.print(" ,Y = ");
  Serial.println(sensorValueY);

  if (sensorValueX > DEFAULT_POSITION + SENSITIVITY_EPSILON) {
    directionR = FORWARD;
    directionL = FORWARD;

    if (sensorValueY < DEFAULT_POSITION) {
      motorValueR = sensorValueX >> 2 + (MAX_10BITS - MAX_POSITION);  // value>>2 == value/4
      motorValueL = (sensorValueX >> 2) - ((DEFAULT_POSITION - sensorValueY) >> 2) + (MAX_10BITS - MAX_POSITION);
    } else {
      motorValueR = (sensorValueX >> 2) - ((sensorValueY - DEFAULT_POSITION) >> 2) + (MAX_10BITS - MAX_POSITION);
      motorValueL = sensorValueX >> 2 + (MAX_10BITS - MAX_POSITION);
    }

  } else {
    if (sensorValueX < DEFAULT_POSITION - SENSITIVITY_EPSILON) {
      directionR = BACKWARDS;
      directionL = BACKWARDS;

      if (sensorValueY < DEFAULT_POSITION) {
        motorValueR = (MAX_10BITS - sensorValueX) >> 2;  // value>>2 == value/4
        motorValueL = ((MAX_10BITS - sensorValueX) >> 2) - ((DEFAULT_POSITION - sensorValueY) >> 2);
      } else {
        motorValueR = ((MAX_10BITS - sensorValueX) >> 2) - ((sensorValueY - DEFAULT_POSITION) >> 2);
        motorValueL = (MAX_10BITS - sensorValueX) >> 2;
      }
    } else {
      if (sensorValueY < DEFAULT_POSITION - SENSITIVITY_EPSILON) {
        directionR = FORWARD;
        directionL = BACKWARDS;
        motorValueR = (MAX_10BITS - sensorValueY) >> 2;  // value>>2 == value/4
        motorValueL = (MAX_10BITS - sensorValueY) >> 2;
      } else {
        if (sensorValueY > DEFAULT_POSITION + SENSITIVITY_EPSILON) {
          directionR = BACKWARDS;
          directionL = FORWARD;
          motorValueR = sensorValueY >> 2 + (MAX_10BITS - MAX_POSITION);
          motorValueL = sensorValueY >> 2 + (MAX_10BITS - MAX_POSITION);
        } else {
          directionR = STOPPED;
          directionL = STOPPED;
          motorValueR = 0;
          motorValueL = 0;
        }
      }
    }
  }
  controlMotor(motorValueL, motorValueR, directionL, directionR);
}


// This procedure handles the joystick switch and updates the LED mode accordingly
void readJoystickSwitch() {
  int SW_value = digitalRead(SW);

  if (SW_value != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (SW_value != buttonState) {
      buttonState = SW_value;

      if (buttonState == LOW) {
        Serial.println("Switch pressed, LED mode updating... ");
        updateLED_Mode();
      }
    }
  }

  lastButtonState = SW_value;
}

// This procedure updates the settings of both motors (speed,direction) based on the given parameters
void controlMotor(uint8_t left_value, uint8_t right_value, motorDirection left_direction, motorDirection right_direction) {
  // set PWM value for both motors
  analogWrite(EN_B, left_value);
  analogWrite(EN_A, right_value);

  //change direction of the left motor
  switch (left_direction) {

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

  // change direction of the right motor
  switch (right_direction) {

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
}


//------------------------------------------------------------------------------
// OTHERS
//------------------------------------------------------------------------------


void blinkBuiltInLed() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
