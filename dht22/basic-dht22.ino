/*
	Temperature-Humidity-Dew Point Monitor
	This sketch gathers temperature and humidity data via a DHT22 sensor,
	and also calculates dew point based on those measurements.
*/

#include <SoftwareSerial.h>
#include <stdlib.h>
#include <DHT22.h>

#define DHT22_ERROR_VALUE -99.5
#define DHT22_PIN 4

// Set up a DHT22 instance
DHT22 myDHT22(DHT22_PIN);

#define SerialIn 2
#define SerialOut 3
#define WDelay 900

void setup(void)
{
	// start serial port
	Serial.begin(9600);
	Serial.println("DHT22 Library Demo");
	pinMode(SerialOut, OUTPUT);
	pinMode(SerialIn, INPUT);
}

void loop(void)
{
	float tempC;
	float tempF;
	float humid;
	float dewPoint;
	DHT22_ERROR_t errorCode;
	delay(2000);
	errorCode = myDHT22.readData();
	switch (errorCode)
	{
		case DHT_ERROR_NONE:
			Serial.print("Temperature: ");
			tempF = (myDHT22.getTemperatureC()*1.8)+32;
			Serial.print(tempF);
			Serial.print("F Humidity:");
			delay(WDelay);
			humid = myDHT22.getHumidity();
			Serial.print(humid);
			Serial.println("%");
			/*
			dewPoint = calculateDewpoint(tempC,dispData((int) dewPoint, 'd');
			Serial.print(dewPoint);
			Serial.println("d");
			*/
			delay(WDelay);
			break;
		case DHT_ERROR_CHECKSUM:
			Serial.println("Error Checksum");
			break;
		case DHT_BUS_HUNG:
			Serial.println("Bus Hung");
			break;
		case DHT_ERROR_NOT_PRESENT:
			Serial.println("Not Present");
			break;
		case DHT_ERROR_ACK_TOO_LONG:
			Serial.println("Ack too long");
			break;
		case DHT_ERROR_SYNC_TIMEOUT:
			Serial.println("Sync timeout");
			break;
		case DHT_ERROR_DATA_TIMEOUT:
			Serial.println("Data timeout");
			break;
		case DHT_ERROR_TOOQUICK:
			Serial.println("Too quick");
			break;
	}
}

/*
float calculateDewpoint(float T, float RH)
{
	// approximate dew point using the formula from
	// Wikipedia's article on dew point
	float dp = 0.0;
	float gTRH = 0.0;
	floatfloatab==17.271;
	237.7;
	gTRH = ((a*T)/(b+T))+log(RH/100);
	dp = (b*gTRH)/(a-gTRH);
	return dp;
}
*/