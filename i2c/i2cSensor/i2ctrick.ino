/*
In this project will use 4 accelerometer MPU6050, 1 clock DS1302, 1 clock DS1307, a barometer DMP180
*/
#include <Wire.h>
#include <RTClib.h>
#include <DS1302.h>
#include <BMP180.h>

//Inizialize the pin of the DS1302
#define SCK_PIN 38
#define IO_PIN 39
#define RST_PIN 40

//Declare DS1307 instance
RTC_DS1307 RTC;
//Declare barometer instance
BMP180 bmp;

char buffer_time[20], bt[5];
char buffer_date[20];
int st;
int num = 4;
//Inizialize a vector with the accelerometer pins
int Acc_pin[] = { 30,31,32,33 };

//Declare DS1302 instance
DS1302 rtc(RST_PIN, IO_PIN, SCK_PIN);

// I2C address of the MPU-6050 when he can send data
const int mpu1 = 0x69;  
//const int mpu2 = 0x68;

int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void DisplayAcc(int MPU) {
  //Return data from the MPU 6050
	Wire.beginTransmission(MPU);
	Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
	Wire.endTransmission(false);
	Wire.requestFrom(MPU, 14, true);  // request a total of 14 registers
	AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
	AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
	AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
	Tmp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
	GyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
	GyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
	GyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
	Serial.println("--------------------");

	Serial.print("Accelerometer: ");
	Serial.print("X = "); Serial.print(AcX);
	Serial.print(" | Y = "); Serial.print(AcY);
	Serial.print(" | Z = "); Serial.println(AcZ);
	//equation for temperature in degrees C from datasheet
	Serial.print("Gyroscope: ");
	Serial.print("X = "); Serial.print(GyX);
	Serial.print(" | Y = "); Serial.print(GyY);
	Serial.print(" | Z = "); Serial.println(GyZ);
	Serial.print("Temperature: "); Serial.print(Tmp / 340.00 + 36.53); Serial.println(" C ");
	Serial.println("--------------------");

}

void DisplayTime(){
  //Return data from the DS1307 and 1302
  DateTime now = RTC.now();
  sprintf(buffer_time,"%02d:%02d:%02d",now.hour(),now.minute(),now.second());
  sprintf(buffer_date,"%02d.%02d.%04d",now.day(),now.month(),now.year());
  Serial.println("--------------------");
  Serial.print("primo : ");
  Serial.print(buffer_time);
  Serial.print(" ");
  Serial.println(buffer_date);
  sprintf(buffer_time, rtc.getTimeStr());
  sprintf(buffer_date, rtc.getDateStr());
  Serial.print("secondo : ");
  Serial.print(buffer_time);
  Serial.print(" ");
  Serial.println(buffer_date);
  Serial.println("--------------------");

}
// Set all accelerometer to address 0x69
void disableAcc() {
	for (int i = 0; i < num; i++) {
		digitalWrite(Acc_pin[i], HIGH);
	}
}
// Set all accelerometer to address 0x68
void enableAcc() {
	for (int i = 0; i < num; i++) {
		digitalWrite(Acc_pin[i], LOW);
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

void DisplayBar()
{
  //Return data from barometer (address 0x77)
	int chk = 0;
	float Pressione_mbar;
	float AltezzaSLM_mt;
	float Temp_gradi;
	chk = leggi_BMP180(&Pressione_mbar, &AltezzaSLM_mt, &Temp_gradi);

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
}
void setup() {
  //Inizialize DS1302
  rtc.halt(false);
  rtc.writeProtect(false);
  Serial.begin(9600);
  //Set all the accelerometer pins to right MODE
  for (int i = 0; i < num; i++) {
    pinMode(Acc_pin[i], OUTPUT);
  }
  //Disable all accelerometer, put all address to 0x69 for comunicate just with the DS1307 that have the 0x68 address
  disableAcc();
  //Inizialize and set the data of the DS1307
  RTC.begin();
  RTC.adjust(DateTime(2018, 11, 20, 14, 42, 00));
  enableAcc();
  rtc.setTime(14, 42, 00);
  rtc.setDate(20, 11, 2018);
  Wire.begin();
  for (int i = 0; i < num; i++) {
    //Enable single Accelerometer, put it to 0x69 address and after close the comunication, change the address to 0x68
    digitalWrite(Acc_pin[i], HIGH);
    Wire.beginTransmission(mpu1);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    digitalWrite(Acc_pin[i], LOW);;
  }
    st=0;
    bmp = BMP180();

    // Controllo di connessione sul sensore BMP180.
    if (bmp.EnsureConnected())
    {
      Serial.println("\n\nConnesso al BMP180.");
      bmp.SoftReset();
      bmp.Initialize();
    }

}

void loop() {
	disableAcc();
  DisplayTime();
	enableAcc();
	DisplayBar();
	for (int i = 0; i < num; i++) {
		digitalWrite(Acc_pin[i], HIGH);
		DisplayAcc(mpu1);
		digitalWrite(Acc_pin[i], LOW);
	}
	//delay(5000);
    st++;

}
