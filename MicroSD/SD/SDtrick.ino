#include <SPI.h>
#include <SD.h>

//Define the pin of the sensor
#define CS_PIN 9
#define SCK_PIN 13
#define MOSI_PIN 11
#define MISO_PIN 12

int sdopn;

void setup()
{
	Serial.begin(9600);
	Serial.println("Inizialize SD...");
  
  //Inizializate MicroSD reader/writer
	sdopn=SD.begin(CS_PIN); 
	if (!SD.begin(CS_PIN)) {
		Serial.println("Failed");
	}
	else {
		Serial.println("Inizialized...");
	}
}

void loop()
{
  //Generate random number to be write
	int rnd = random(0, 1000);
  
  //if the sd is inizialized
	if (sdopn) {
		Serial.println("Open File");
    //Open file in write mode, if the file doesn't exit will be create, 
    // if the file exits the data will be append at the end
		File myFile = SD.open("prova.txt", FILE_WRITE);
		if (!myFile) {
			Serial.println("Failed");
		}
		else {
      //print the data inside the file and on the Serial port
			Serial.print("numero scelto=");
			Serial.println(rnd);
			myFile.println(rnd);
			myFile.close();
			Serial.println("Writing");
			
		}
	}
	else {
    //if the memory card is not read try again to inizialize
		sdopn = SD.begin(CS_PIN);
		if (!SD.begin(CS_PIN)) {
			Serial.println("SD open Failed");
		}
	}
	delay(2000);

}
