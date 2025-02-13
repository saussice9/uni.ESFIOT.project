// Project made for an Arduino Uno

// Motors and LED handling

// ---------------------------------------------------------
// Include Libraries
// ---------------------------------------------------------

#include <Adafruit_NeoPixel.h>  // Library to control the NeoPixel LED strip
#ifdef __AVR__
  #include <avr/power.h>  // Needed for Adafruit Trinket 16 MHz
#endif

#include <SoftwareSerial.h>  // Library to use the HC05 Bluetooth module

// ---------------------------------------------------------
// Types declaration
// ---------------------------------------------------------
typedef unsigned int uint;

typedef enum {
  STOPPED,
  BACKWARDS,
  FORWARD
} motorDirection;

// ---------------------------------------------------------
// Macros
// ---------------------------------------------------------

#define PIN_NEOPIXEL 4  // Data pin for the LED strip
#define NUM_PIXELS 64   // Number of NeoPixels

// Left motor
#define EN_B 5
#define IN_4 6
#define IN_3 7

// Right motor
#define IN_2 8
#define IN_1 9
#define EN_A 10

#define n_color 4
uint colors[n_color][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 0, 50, 50 }, { 69, 6, 23 } };  // default display for the NeoPixels
#define n_color2 3
uint colors2[n_color2][3] = { { 100, 0, 0 }, { 0, 100, 0 }, { 50, 50, 50 } };  // Italy display
#define n_color3 3
uint colors3[n_color3][3] = { { 100, 0, 0 }, { 50, 50, 50 }, { 0, 0, 100 } };  // France display
#define n_color4 7
uint colors4[n_color4][3] = { { 30, 2, 50 }, { 0, 0, 100 }, { 5, 50, 30 }, { 0, 100, 0 }, { 50, 40, 0 }, { 75, 15, 0 }, { 100, 0, 0 } };  // rainbow display

// ---------------------------------------------------------
// Global Variables
// ---------------------------------------------------------

int shift = 0;
int mode = 2;
uint counter_change_mode = 0;
int n_same = 0; // test purpose only

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);  // Setting NeoPixels configuration

uint8_t motorValueR = 0;
uint8_t motorValueL = 0;

motorDirection directionR = STOPPED;
motorDirection directionL = STOPPED;

// ---------------------------------------------------------
// Routine prototypes
// ---------------------------------------------------------

void printLED();
void demoOne();
void demoTwo();
void readJoystick();


// ---------------------------------------------------------
// Setup procedure
// ---------------------------------------------------------
// This function runs once at the beginning

void setup() {
  Serial.begin(9600);  // Serial communication initialization

  pinMode(EN_A, OUTPUT);  // Setting enable right motor (pin 10) as output
  pinMode(EN_B, OUTPUT);  // Setting enable left  motor (pin 5) as output
  pinMode(IN_1, OUTPUT);  // Setting left motor (pin 9) as output
  pinMode(IN_2, OUTPUT);  // Setting left motor (pin 8) as output
  pinMode(IN_3, OUTPUT);  // Setting right motor (pin 7) as output
  pinMode(IN_4, OUTPUT);  // Setting right motor (pin 6) as output

  pinMode(PIN_NEOPIXEL, OUTPUT);  // Setting Neopixel pin (pin 4) as output
  digitalWrite(PIN_NEOPIXEL, LOW);


#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);  // Code spécifique pour Adafruit Trinket 5V 16 MHz
#endif

  pixels.begin();  // NeoPixel initialization

  printLED();
}

// ---------------------------------------------------------
// Main Loop Procedure
// ---------------------------------------------------------
// This function runs over and over again

void loop() {
  demoOne();
  delay(1000);
  demoTwo();
  delay(1000);
}

void printLED() {
  Serial.println("printLED");
  if (counter_change_mode > 50) {
    if (mode >= 8) {
      mode = 0;
    } else {
      mode += 1;
    }
    counter_change_mode = 0;
    Serial.print("   Manual mode    ");
    Serial.println(mode);
  } else {
    counter_change_mode++;
  }

  switch (mode) {    // LED display mode
    pixels.clear();  // Switch off all the pixels

    case 00:
      Serial.println("LED mode 0");
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(colors[(shift + i) % n_color][0], colors[(shift + i) % n_color][1], colors[(shift + i) % n_color][2]));

        // Send the updated pixel colors to the hardware.4
      }
      pixels.show();

      break;

    case 01:

      Serial.println("LED mode 1");
      if (shift >= n_color - 1) {
        shift = 0;
      } else {
        shift++;
      }

      digitalWrite(LED_BUILTIN, HIGH);        // will turn the LED on
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(colors[(shift + i) % n_color][0], colors[(shift + i) % n_color][1], colors[(shift + i) % n_color][2]));

        // Send the updated pixel colors to the hardware.
      }
      pixels.show();

      break;

    case 02:

      Serial.println("LED mode 2");
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(colors2[(shift + i) % n_color2][0], colors2[(shift + i) % n_color2][1], colors2[(shift + i) % n_color2][2]));

        // Send the updated pixel colors to the hardware.
      }
      pixels.show();

      break;

    case 03:

      if (shift >= n_color2 - 1) {
        shift = 0;
      } else {
        shift++;
      }

      Serial.println("LED mode 3");
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(colors2[(shift + i) % n_color2][0], colors2[(shift + i) % n_color2][1], colors2[(shift + i) % n_color2][2]));

        // Send the updated pixel colors to the hardware.
      }
      pixels.show();

      digitalWrite(LED_BUILTIN, LOW);  // will turn the LED off

      break;

    case 04:
      Serial.println("LED mode 4");
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(colors3[(shift + i) % n_color3][0], colors3[(shift + i) % n_color3][1], colors3[(shift + i) % n_color3][2]));

        // Send the updated pixel colors to the hardware.
      }
      pixels.show();
      break;

    case 05:

      if (shift >= n_color3 - 1) {
        shift = 0;
      } else {
        shift++;
      }

      Serial.println("LED mode 5");
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(colors3[(shift + i) % n_color3][0], colors3[(shift + i) % n_color3][1], colors3[(shift + i) % n_color3][2]));

        // Send the updated pixel colors to the hardware.
      }
      pixels.show();

      break;

    case 06:
      Serial.println("LED mode 6");
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));

        // Send the updated pixel colors to the hardware.
      }
      pixels.show();

      break;

    case 07:

      if (shift >= n_color4 - 1) {
        shift = 0;
      } else {
        shift++;
      }

      Serial.println("LED mode 7");
      for (int i = 0; i < NUM_PIXELS; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));

        // Send the updated pixel colors to the hardware.
      }
      pixels.show();

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
        for (int i = 0; i < n_same; i++) {  //les premiers pixels
          pixels.setPixelColor(i, pixels.Color(colors4[(shift - 1) % n_color4][0], colors4[(shift - 1) % n_color4][1], colors4[(shift - 1) % n_color4][2]));
        }
      }

      Serial.println("LED mode 0");
      for (int i = 0; i < NUM_PIXELS - 1 / 4; i++) {  // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i * 4 + n_same, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
        pixels.setPixelColor((i * 4 + 1 + n_same) % NUM_PIXELS, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
        pixels.setPixelColor((i * 4 + 2 + n_same) % NUM_PIXELS, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));
        pixels.setPixelColor((i * 4 + 3 + n_same) % NUM_PIXELS, pixels.Color(colors4[(shift + i) % n_color4][0], colors4[(shift + i) % n_color4][1], colors4[(shift + i) % n_color4][2]));

        // Send the updated pixel colors to the hardware.4
      }
      pixels.show();

      break;

    default:

      Serial.println(F("LED off"));
      pixels.show();
      digitalWrite(LED_BUILTIN, LOW);  // will turn the LED off

      break;
  }
}

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
  // read the value from the sensor:
  int sensorValueY = analogRead(A0);  // variable to store the value coming from the sensor
  int sensorValueX = analogRead(A1);  // variable to store the value coming from the sensor

  Serial.println("valeur des axes :");
  Serial.println(sensorValueY);
  Serial.println(sensorValueX);

  if (sensorValueY > 800) motorValueL = 0xFF;
  if (sensorValueY < 300) motorValueR = 0xFF;
  if (sensorValueX > 900) {
    motorValueL = 0xFF;
    motorValueR = 0xFF;
  }
}
