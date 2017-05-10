#include <Wire.h>
#include <BMP180.h> //import the library

BMP180 bmp;
//float seaLevel = 101325; //enable this for seaLevel Altitude

void setup()
{
	Serial.begin(9600);
	Wire.begin();
	bmp = BMP180();

	// Check connection with BMP180.
	if (bmp.EnsureConnected())
	{
		Serial.println("\n\nConnesso al BMP180.");
		bmp.SoftReset();
		bmp.Initialize();
	}
}

int leggi_BMP180(float* press, float* alt, float* temp) {
	if (bmp.IsConnected) {
		*press = bmp.GetPressure();
		*alt = bmp.GetAltitude(*press); // press = altitude from previus, if use seaLevel variable from seaLevel
		*press = *press / 100;
		*temp = bmp.GetTemperature();
		return(1);
	}
	else {
		return 0;
	}
}

void loop()
{
	int chk = 0;
	float Pressione_mbar;
	float AltezzaSLM_mt;
	float Temp_gradi;
  
	chk = leggi_BMP180(&Pressione_mbar, &AltezzaSLM_mt, &Temp_gradi); //Read data from barometer

	if (chk) {
		Serial.println("--------------------");
		Serial.print("Pressione = ");
		Serial.println(Pressione_mbar);
		Serial.print("Altezza = ");
		Serial.println(AltezzaSLM_mt);
		Serial.print("Temperatura = ");
		Serial.println(Temp_gradi);
		Serial.println("--------------------");
	}
	else {
		Serial.println("Problema di lettura col sensore");
	}

	delay(5000); // Cinque secondi di pausa prima della prossima lettura

}
