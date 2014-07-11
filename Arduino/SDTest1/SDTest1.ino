#include <stdarg.h>
#include <DHT.h>
#include <SD.h>

File datafile;
DHT dht_1;
DHT dht_2;

//	Constants.

const int sd_card_select_pin = 10;
const int dht_1_pin = 4;
const int dht_2_pin = 3;

const int delay_between_reads = 1000; //Number of milliseconds to delay between successive reads of temperature/humidity

//	Global variables.
boolean initOK;

void setup ()
{
	//	Clear out the previous Serial console contents
	Serial.flush();

	//	Everything is OK by default.
	initOK = true;

	//	Initialize our serial (console) output
	Serial.begin(9600);		//	Set the baud rate of the console
	Serial.println("INIT");	//	Write "INIT" to the top line of the console

	//	Initalize the DHT22 sensor.
	Serial.println("    initializing dht_1...");
	dht_1.setup(dht_1_pin);		//	Set it up with its data pin
	dht_2.setup(dht_2_pin);		//	Ditto.

	//	Initialize the SD card.
	Serial.println("    initializing sd card...");
	pinMode(sd_card_select_pin, OUTPUT);	//	pin 10 is used by the SD card
	if ( ! SD.begin(sd_card_select_pin) )
	{
		initOK = false;
		Serial.println("    ERROR: failed to initialize sd card!");
	}
	else
	{
		//	Continue with setting up our file.
		datafile = SD.open("data.log", FILE_WRITE);
		if ( ! datafile )
		{
			initOK = false;
			Serial.println("    ERROR: failed to open file for output!");
		}
		else
		{
			datafile.flush();			//	Flush out any old data from a previous run.
			datafile.println("BEGIN");
			datafile.flush();			//	We have to flush() data with every write.
		}
	}

	if ( ! initOK )
	{
		Serial.println("INIT FAILED");
	}
	else
	{
		Serial.println("INIT SUCCESS");
	}
        delay(5000);
}

/*
char *float_to_string (double f)
{
	int precision = 2;
	char a[128];
	char *ret = a;
	long integer = (long)f;
	itoa(integer, a, 10);
	while (*a != '\0') a++;
	*a++ = '.';
	long decimal = abs((long)((f - integer) * 100));
	itoa(decimal, a, 10);
	*a++ = '\0';
	return a;
}

void safe_output(char *fmt, ... )
{
	//	With help from http://playground.arduino.cc/Main/Printf
	char tmp[128];		//	output string will be limited to 128 chars
	va_list args;
	va_start (args, fmt);
	vsnprintf(tmp, 128, fmt, args);
	va_end (args);
	datafile.print(tmp);
	datafile.flush();
	Serial.print(tmp);
	Serial.flush();
}
*/

void printReadings(File theFile, float theTemperature, float theHumidity)
{
}

void loop ()
{
	if ( initOK )
	{
		//safe_output("%s\n", float_to_string(5.0));
		//safe_output("%s %f %f\n", dht_1.getStatusString(), dht_1.toFahrenheit(dht_1.getTemperature()), dht_1.getHumidity());
                
		Serial.print("dht_1 ");
		datafile.print("dht_1 ");
                Serial.print(millis());
                Serial.print(": ");
		Serial.print(dht_1.toFahrenheit(dht_1.getTemperature()));
                datafile.print(millis());
                datafile.print(": ");
		datafile.print(dht_1.toFahrenheit(dht_1.getTemperature()));
		Serial.print(' ');
		datafile.print(' ');
		Serial.println(dht_1.getHumidity());
		datafile.println(dht_1.getHumidity());
		Serial.flush();
		datafile.flush();
		Serial.print("dht_2 ");
		datafile.print("dht_2 ");
                Serial.print(millis());
                Serial.print(": ");
		Serial.print(dht_2.toFahrenheit(dht_2.getTemperature()));
                datafile.print(millis());
                datafile.print(": ");
		datafile.print(dht_2.toFahrenheit(dht_2.getTemperature()));
		Serial.print(' ');
		datafile.print(' ');
		Serial.println(dht_2.getHumidity());
		datafile.println(dht_2.getHumidity());
		Serial.flush();
		datafile.flush();
                delay(delay_between_reads);
	}
}
