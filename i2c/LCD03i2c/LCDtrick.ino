#include <Wire.h>
#include <LCD03.h>

// Create new LCD03 instance
LCD03 lcd;

int st;
void setup()
{	
  //Inizialize the dimension of the screen, columns and rows
	lcd.begin(20, 4); 

	//Turn off the backlight
	lcd.noBacklight();
  Serial.begin(9600);
	st = 0;
}

void loop()
{
	lcd.home();          
  
  // Print a message to the LCD.
	lcd.println("Hello, world!");
	lcd.print(st);
  
	Serial.print("cycle number: ");
	Serial.println(st);
	st++;
	delay(1000);
}
