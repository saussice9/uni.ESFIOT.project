// TI_MSP432P401R (+ shield) application to control DiscoBot

// Pin numbers
#define JOYSTICK_SEL  5  // the number of the joystick select pin
#define JOYSTICK_X 2    // the number of the joystick X-axis analog
#define JOYSTICK_Y 26   // the number of the joystick Y-axis analog

// Baud rates
#define SERIAL_RATE 9600
#define BT_RATE 57600

/**
* @brief Last time the joystick button state was debounced.
* @details Used for timing in the debounce mechanism.
*/
unsigned long lastDebounceTime = 0;

/**
* @brief Time interval required between state changes for debouncing.
* @details Defines how long to wait before accepting a button state change.
*/
const unsigned long debounceDelay = 50;

/**
* @brief Previous state of the joystick button.
* @details Used to detect changes in button state.
*/
int lastButtonState = HIGH;

/**
* @brief Current debounced state of the joystick button.
* @details Represents the validated button state after debouncing.
*/
int buttonState;

/**
* @brief Handles joystick button state.
* @details Implements debounce logic and mode switching.
*/
void readJoystickSwitch() {
  int JOYSTICK_SEL_state = digitalRead(JOYSTICK_SEL);
  
  if (JOYSTICK_SEL_state != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (JOYSTICK_SEL_state != buttonState) {
      buttonState = JOYSTICK_SEL_state;
    }
  } 
  lastButtonState = JOYSTICK_SEL_state;
}


void setup() {

  // initialize the pushbutton pin as an input:
  pinMode(JOYSTICK_SEL, INPUT_PULLUP);
  Serial.begin(SERIAL_RATE);
  Serial1.begin(BT_RATE);
}

void loop() {
  readJoystickSwitch();
  if (buttonState == HIGH) {
    
    // read the analog value of joystick two axis
    int JOYSTICK_X_state = analogRead(JOYSTICK_X);
    int JOYSTICK_Y_state = analogRead(JOYSTICK_Y);

    // Write to serial monitor
    Serial.write("*X");
    Serial.print(JOYSTICK_X_state / 4);
    Serial.write(",Y");
    Serial.print(JOYSTICK_Y_state / 4);
    Serial.write("_");


    // Bluetooth sent data 
    // Here, we need to swap X and Y because there are reversed in comparison with the axis used in the Arduino code for the joystick.
    // Also we divide by 4 because the values received from the joystick are on 10 bits (from 0 to 1023) and we need to have them on 8 bits (from 0 to 255) to
    // send them in a fluid way via Bluetooth.
    // After reception, these values are likely to be multiplied by 4.

    Serial1.write("*X");
    Serial1.print(JOYSTICK_Y_state / 4);
    Serial1.write(",Y");
    Serial1.print(JOYSTICK_X_state / 4);
    Serial1.write("_");

  } else {
    // change mode by pressing the joystick switch
    
    Serial1.write("M");
    Serial.write("M");
  }
  delay(400);
}