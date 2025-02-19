# DiscoBot

*Let's groove, folks !*

## Project description

This project is called **DiscoBot**. It consists in a robot that can be controlled via Bluetooth or via an analog joystick thanks to two DC motors. The robot is also equipped with a strip led (8 different patterns) and a buzzer that can play short famous music tracks.

## Project components

Main components:

- 1 Arduino Mega 2560 (robot controller)
- 1 Texas Instrument MSP432P401R (remote)
- 2 Bluetooth module HC-05 (master and slave)
- 1 L298N DC motors driver
- 2 DC motors
- 1 SK6812 strip led
- 1 sound buzzer
- 1 5V battery for the Arduino
- 1 9V battery for the motors and the L298N

Additional components:
- 1 smartphone to send commands to the robot instead of the TI board

## About the boards

The robot is controlled by the Arduino Mega 2560. One can use another Arduino board like the Arduino Uno or the Arduino Nano (if the code storage is big enough).

A TI MSP432P401R board is used as a remote control. It can be used to send commands to the robot in order to move it or to change the led pattern and buzzer music.

## Power
The robot is powered by two batteries:
- 5V for the Arduino and its peripherals
- 9V for the motors and the L298N

## How to use it ?

Power both boards and make sure that the one HC-05 is the master and the other one is the slave and that they communicate with the same baud rate.
After the connection, the robot is ready to be controlled.
To control it you can use either the TI board or your smartphone.

If you use you smartphone, make sure that the data is formatted as follows: "*X<X_value>,Y<Y_value>_".
The '\*' prefix character indicates that the data is about the coordinates of the joystick, not about the LED mode.
The '\_' suffix character is the end character.
The coordinate values must be between 0 and 255.

## About us
We are 4 students from the university of Trento in Italy.

Nathan PERDOUX (Bluetooth receiving, Arduino Mega architecture code, documentation, buzzer, joystick input)
Killian LASSAIGNE (Motors, strip LED, buzzer, powering)
Gulio CAMPANA (Bluetooth transmitting, TI part)
Lorenzo Ciro LUONGO (Bluetooth transmitting, TI part)