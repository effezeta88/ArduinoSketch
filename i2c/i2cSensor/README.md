##HOW it WORKS

In this example we use 4 accelerometers MPU6050, they have i2c address 0x68 and 0x69,
a real time clock DS1302, a real time clock DS1307 with i2c address 0x68,
a barometer BMP180 i2c address 0x77.
For comunicate all this sensor that have the same i2c address we have created and invented a "protocol" in which
each accelerometer start to the same address (0x68) and when one have to send data it change its address to 0x69.
When it is finished come back to the previous address.
When is the Real Time DS1307 to talk, all the accelerometers change its address to 0x69, so the address 0x68 is
free for the comunication of the clock. After that all the accelerometer come back to the previous address.
For the barometer we don't have a this problem because it have a different address.
The other clock works with a normal digital pins.
