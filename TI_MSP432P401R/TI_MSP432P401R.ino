// TI_MSP432P401R (+ shield) application to control DiscoBot

// Pin numbers
#define JOYSTICK_SEL  5  // the number of the joystick select pin
#define JOYSTICK_X 2    // the number of the joystick X-axis analog
#define JOYSTICK_Y 26   // the number of the joystick Y-axis analog

// Baud rates
#define SERIAL_RATE 9600
#define BT_RATE 57600

void setup() {

  // initialize the pushbutton pin as an input:
  pinMode(JOYSTICK_SEL, INPUT_PULLUP);
  Serial.begin(SERIAL_RATE);
  Serial1.begin(BT_RATE);
}

void loop() {
  int JOYSTICK_SEL_state = digitalRead(JOYSTICK_SEL);
  if (JOYSTICK_SEL_state == HIGH) {
    
    // read the analog value of joystick two axis
    int JOYSTICK_X_state = analogRead(JOYSTICK_X);
    int JOYSTICK_Y_state = analogRead(JOYSTICK_Y);

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