// Project made for an Arduino Uno
// This project is a simple robot that can be controlled by a smartphone via Bluetooth (not effective yet)
// The robot is equipped with a NeoPixel LED strip that can display different colors and patterns
// The robot is also equipped with two DC motors that can be controlled by the board

//=============================================================================
//                              INCLUDE LIBRARIES
//=============================================================================

//------------------------------------------------------------------------------
// DEBUG
//------------------------------------------------------------------------------

#include <Bonezegei_Printf.h>

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

//------------------------------------------------------------------------------
// BUZZER
//------------------------------------------------------------------------------

#include "buzzer.h"

//=============================================================================
//                              TYPE DECLARATIONS
//=============================================================================

typedef unsigned int uint;

//------------------------------------------------------------------------------
// MOTORS
//------------------------------------------------------------------------------

typedef enum driveMode_t {
  STOPPED,
  BACKWARDS,
  FORWARD
} driveMode_t;

//=============================================================================
//                                   MACROS
//=============================================================================

//------------------------------------------------------------------------------
// DEBUG
//------------------------------------------------------------------------------

// #define DEBUG_STRIP_LED  // Uncomment to enable strip LED debug messages
 #define DEBUG_JOYSTICK  // Uncomment to enable joystick debug messages
 #define DEBUG_MOTORS    // Uncomment to enable motors debug messages


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

#define FULL_SPEED 100

// Joystick sensitivity arbitrary quantum
#define SENSITIVITY_EPSILON 50

// Default position of X and Y when the joystick is untouched
#define DEFAULT_POSITION 520
#define MAX_POSITION 1023
#define MIN_POSITION 0
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

//------------------------------------------------------------------------------
// BUZZER
//------------------------------------------------------------------------------

#define BUZZER_PIN  2

//=============================================================================
//                             GLOBAL VARIABLES
//=============================================================================

//------------------------------------------------------------------------------
// DEBUG
//------------------------------------------------------------------------------

Bonezegei_Printf debug(&Serial);  // enable printf

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

int shift = 0;
int mode = 0;
int n_same = 0;  // test purpose only

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);  // Setting NeoPixels configuration

//------------------------------------------------------------------------------
// MOTORS AND JOYSTICK
//------------------------------------------------------------------------------

// Motors
uint8_t motorSpeedR = 0;
uint8_t motorSpeedL = 0;

driveMode_t driveModeR = STOPPED;
driveMode_t driveModeL = STOPPED;

const float MOTOR_SCALING_FACTOR = (float)DEFAULT_POSITION / FULL_SPEED;

//Joystick

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = HIGH;
int buttonState;

//------------------------------------------------------------------------------
// BUZZER
//------------------------------------------------------------------------------

int note = 0;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

void updateLED_Display();
void updateLED_Mode();
char* getPatternName(int mode);

//------------------------------------------------------------------------------
// MOTORS AND JOYSTICK
//------------------------------------------------------------------------------

void demoOne();
void demoTwo();
void demoThree();
void readJoystick();
void readJoystickSwitch();
void resetMotorStates();
uint8_t intToUint8_t(int integer_value);
void applyMotorsSpeed();
void applyDriveModes();
void applyMotorsSettings();
char* getDirectionName(driveMode_t direction);

//------------------------------------------------------------------------------
// BUZZER
//------------------------------------------------------------------------------

void buzz();

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

//=============================================================================
//                             PROCEDURE DEFINITIONS
//=============================================================================

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
// MOTORS AND JOYSTICK
//------------------------------------------------------------------------------

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

// This procedure set both the motors to STOPPED state and with a speed of 0
void resetMotorStates() {
  driveModeR = STOPPED;
  driveModeL = STOPPED;
  motorSpeedR = 0;
  motorSpeedL = 0;
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

// This procedure updates the motors speed based on the related global variables
void applyMotorsSpeed() {

  // set PWM value for both motors
  analogWrite(EN_A, motorSpeedR );
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

//------------------------------------------------------------------------------
// BUZZER
//------------------------------------------------------------------------------
void buzz(){
  
  if ( mode>=0 && mode < 8 ){
    
    int scaled_mode = mode%4; 
    
    if (note < size_tab[scaled_mode]) {

      int* tab_duration = (int*)durations_tab[scaled_mode];
      int* tab_melody = (int*)melody_tab[scaled_mode];
      
      //to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int duration = 1000 / tab_duration[note];
      tone(BUZZER_PIN, tab_melody[note], duration);
      
      //to distinguish the notes, set a minimum time between them.
      //the note's duration + 20% seems to work well:
      int pauseBetweenNotes = duration * 1.20;
      delay(pauseBetweenNotes);
      
      //stop the tone playing:
      noTone(BUZZER_PIN);
      note++;
    }else{
      noTone(BUZZER_PIN);
      delay(100);
    }
  } else{
    delay(100);
  }
}

//------------------------------------------------------------------------------
// OTHERS
//------------------------------------------------------------------------------

// This procedure blinks the built-in LED
void blinkBuiltInLed() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
