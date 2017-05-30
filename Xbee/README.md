## Xbee communication in AT##

Point to point communication

Use two Xbee boards on Arduino Uno to send data from a Joystick Analogic and lights on a RBG LED.
The data is read from an Analog pins and send to the Serial Xbee, which trasmitt the direction of the movement to the other Xbee. The Arduino show the data over a LCD screen link with the I2C protocol and Light on a RGB LED with different colours agree with the direction received.
