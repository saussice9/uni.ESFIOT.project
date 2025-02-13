// Project made for an Arduino Uno
// This project is a simple robot that can be controlled by a smartphone via Bluetooth (not effective yet)
// The robot is equipped with a NeoPixel LED strip that can display different colors and patterns
// The robot is also equipped with two DC motors that can be controlled by the Arduino

//=============================================================================
//                              INCLUDE LIBRARIES
//=============================================================================


//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

#include <Adafruit_NeoPixel.h>  // Library to control the NeoPixel LED strip
#ifdef __AVR__
#include <avr/power.h>  // Needed for Adafruit Trinket 16 MHz
#endif


//------------------------------------------------------------------------------
// BLUETOOTH
//------------------------------------------------------------------------------

#include <SoftwareSerial.h>  // Library to use the HC05 Bluetooth module


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
// MOTORS
//------------------------------------------------------------------------------

// Left motor
#define EN_B 5
#define IN_4 6
#define IN_3 7

// Right motor
#define IN_2 8
#define IN_1 9
#define EN_A 10

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
int n_same = 0; // test purpose only

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);  // Setting NeoPixels configuration

//------------------------------------------------------------------------------
// MOTORS
//------------------------------------------------------------------------------

uint8_t motorValueR = 0;
uint8_t motorValueL = 0;

motorDirection directionR = STOPPED;
motorDirection directionL = STOPPED;

//=============================================================================
//                           ROUTINE PROTOTYPES
//=============================================================================

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------
void updateLED_Display();
void updateLED_Mode();

//------------------------------------------------------------------------------
// MOTORS
//------------------------------------------------------------------------------

void demoOne();
void demoTwo();
void readJoystick();
void controlMotor(uint8_t left_value, uint8_t right_value, motorDirection left_direction, motorDirection right_direction);

//=============================================================================
//                             SETUP PROCEDURE
//=============================================================================

// This procedure runs once at the beginning

void setup() {
  Serial.begin(9600);  // Serial communication initialization
  
  pinMode(EN_A, OUTPUT);  // Setting enable right motor (pin 10) as output
  pinMode(EN_B, OUTPUT);  // Setting enable left  motor (pin 5) as output
  pinMode(IN_1, OUTPUT);  // Setting left motor (pin 9) as output
  pinMode(IN_2, OUTPUT);  // Setting left motor (pin 8) as output
  pinMode(IN_3, OUTPUT);  // Setting right motor (pin 7) as output
  pinMode(IN_4, OUTPUT);  // Setting right motor (pin 6) as output
  
  pinMode(SW, INPUT_PULLUP);      // Setting joystick switch as pull-up input
  
  pinMode(PIN_NEOPIXEL, OUTPUT);  // Setting Neopixel pin (pin 4) as output
  digitalWrite(PIN_NEOPIXEL, LOW);
  
  pixels.begin();  // NeoPixel initialization
  
  updateLED_Display();
}

//=============================================================================
//                             MAIN LOOP PROCEDURE
//=============================================================================

void loop() {
  // demoOne();
  // delay(1000);
  // demoTwo();
  // delay(1000);
  
  // controlMotor(200,200,FORWARD,BACKWARDS);
  // delay(2000);
  // controlMotor(100,20,STOPPED,BACKWARDS);
  // delay(2000);

  delay(100);
  readJoystick();
  updateLED_Display();
}

//=============================================================================
//                             PROCEDURE DEFINITIONS
//=============================================================================

//------------------------------------------------------------------------------
// LED STRIP
//------------------------------------------------------------------------------

void updateLED_Display() {
/* if (counter_change_mode > 50) {
    updateLED_Mode();
    counter_change_mode = 0;
  } else {
    counter_change_mode++;
  } */
  
  pixels.clear();  // Switch off all the pixels

  switch (mode) {    // LED display mode
    
    case 0:
        for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...
          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(colors[(shift + i) % n_color][0], colors[(shift + i) % n_color][1], colors[(shift + i) % n_color][2]));
        }
        break;

    case 1:
    
        if (shift >= n_color - 1) 
        {
          shift = 0;
        } 
        else 
        {
          shift++;
        }
        
        for (int i = 0; i < NUM_PIXELS; i++) // For each pixel...
        {   
          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(colors[(shift + i) % n_color][0], colors[(shift + i) % n_color][1], colors[(shift + i) % n_color][2]));
        }
        break;
        
    case 2:
  
        Serial.println("LED mode 2");
        for (int i = 0; i < NUM_PIXELS; i++)  // For each pixel...
        {  
          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(colors2[(shift + i) % n_color2][0], colors2[(shift + i) % n_color2][1], colors2[(shift + i) % n_color2][2]));
        }
        break;
    
    case 3:
    
        if (shift >= n_color2 - 1) 
        {
          shift = 0;
        } 
        else 
        {
          shift++;
        }
        
        for (int i = 0; i < NUM_PIXELS; i++)  // For each pixel...
        {  
          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(colors2[(shift + i) % n_color2][0], colors2[(shift + i) % n_color2][1], colors2[(shift + i) % n_color2][2]));
        }
        break;
        
    case 4:
        for (int i = 0; i < NUM_PIXELS; i++) // For each pixel... 
        {  
          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(colors3[(shift + i) % n_color3][0], colors3[(shift + i) % n_color3][1], colors3[(shift + i) % n_color3][2]));
        }
        break;
        
    case 5:
        if (shift >= n_color3 - 1) 
        {
          shift = 0;
        } 
        else 
        {
          shift++;
        }
        
        for (int i = 0; i < NUM_PIXELS; i++)  // For each pixel...
        {  
          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(colors3[(shift + i) % n_color3][0], colors3[(shift + i) % n_color3][1], colors3[(shift + i) % n_color3][2]));
        }
        break;
        
    case 6:
        for (int i = 0; i < NUM_PIXELS; i++)   // For each pixel...
        {
          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
        }
        break;
        
    case 7:
        
        if (shift >= n_color4 - 1) 
        {
          shift = 0;
        } 
        else 
        {
          shift++;
        }
        
        for (int i = 0; i < NUM_PIXELS; i++)   // For each pixel...
        {
          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
        }
        break;
        
    case 8:
        if (n_same >= 4) 
        {
          if (shift <= 0) 
          {
            shift = n_color4 - 1;
          } 
          else 
          {
            shift--;
          }
          n_same = 0;
        } 
        else 
        {
          n_same++;
          for (int i = 0; i < n_same; i++) // the first pixels
          {  
            pixels.setPixelColor(i, pixels.Color(colors4[(shift - 1) % n_color4][0], colors4[(shift - 1) % n_color4][1], colors4[(shift - 1) % n_color4][2]));
          }
        }
        
        for (int i = 0; i < NUM_PIXELS - 1 / 4; i++) // For each pixel...
        {  
          
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

void updateLED_Mode(){
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
// MOTORS
//------------------------------------------------------------------------------

void demoOne() {
  // cette fonction fera tourner les moteurs dans les deux sens à une
  //vitesse fixe
  // allume le moteur A
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  // définit la vitesse à 200 sur la plage possible 0 ~ 255
  analogWrite(EN_A, 200);
  // allume le moteur B
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  // définit la vitesse à 200 sur la plage possible 0 ~ 255
  analogWrite(EN_B, 200);
  delay(2000);
  // change maintEN_Ant les directions du moteur
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  delay(2000);
  // Désactive maintEN_Ant les moteurs
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

void demoTwo() {
  // cette fonction fait tourner les moteurs dans la gamme des vitesses possibles
  // noter que la vitesse maximale est déterminée par le moteur lui-même et la tension de fonctionnement
  // les valeurs PWM envoyées par analogWrite () sont des fractions de la vitesse maximale possible
  // votre matériel
  // allume les moteurs
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  // accélérer de zéro à la vitesse maximale
  for (int i = 0; i < 256; i++) {
    analogWrite(EN_A, i);
    analogWrite(EN_B, i);
    delay(20);
  }
  // décélération de la vitesse maximale à zéro
  for (int i = 255; i >= 0; i--) {
    analogWrite(EN_A, i);
    analogWrite(EN_B, i);
    delay(20);
  }
  // Désactive maintEN_Ant les moteurs
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

void readJoystick() {

  int val_SW = digitalRead(SW);
  
  Serial.print("Switch state: ");
  Serial.println(val_SW);
  if(!val_SW){
    Serial.println("Switch pressed, LED mode updating... ");
    updateLEDMode();
  }

  // read the value from the sensor between 0 and 1023:
  int sensorValueY = analogRead(A0);  // variable to store the value coming from the sensor
  int sensorValueX = analogRead(A1);  // variable to store the value coming from the sensor
  
  Serial.print("Axis values: ");
  Serial.print("X = ");
  Serial.print(sensorValueX);
  Serial.print(" ,Y = ");
  Serial.println(sensorValueY);

  /*if (sensorValueX > 800){
    directionR = FORWARD;
    directionL = FORWARD;
    motorValueL = (sensorValueX + sensorValueY)/8
    if((sensorValueX - sensorValueY)<0){
      motorValueR = 0;
    }else{
      motorValueR = (sensorValueX - sensorValueY)/8;
    }

  }else{
    if(sensorValueX < 250){
      directionR = BACKWARDS;
      directionL = BACKWARDS;
    }else{
      
    }
    
  }*/

  controlMotor(255, 255, directionL,  directionR); 

  /*if (sensorValueY < 300) motorValueR = 0xFF;
  if (sensorValueX > 900) {
  motorValueL = 0xFF;
  motorValueR = 0xFF;
  }*/

}

void controlMotor(uint8_t left_value, uint8_t right_value, motorDirection left_direction, motorDirection right_direction){
  //set PWM for motors
  analogWrite(EN_A, right_value);
  analogWrite(EN_B, left_value);
  
  //change direction of the right motor
  switch (right_direction){
    
    case FORWARD:
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
    break;
    
    case BACKWARDS:
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
    break;
    
    default:
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
    break;
  }
  
  //change direction of the left motor
  switch (left_direction){
    
    case FORWARD:
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
    break;
    
    case BACKWARDS:
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
    break;
    
    default:
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
    break;
  }
}