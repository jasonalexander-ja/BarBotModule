#include <Arduino.h>
#include <Wire.h>
#include <Unit.h>


/*
This is just utility setup code for communicating with the controller ext.

For programming your module please edit `Unit.cpp` in the `lib/Unit` folder, 
and ignore this file. 
*/


uint8_t option = 0;
bool isRunning = false;
char lastRunResult = 0;

void receiveEvent(int howMany);
void requestEvent();

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	unitSetup();
	Wire.begin(UNIT_ADDRESS);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
}

void loop()
{
	digitalWrite(LED_BUILTIN, HIGH);
	delay(50);
	if (isRunning)
	{
		lastRunResult = performAction(option);
		isRunning = false;
	}
	digitalWrite(LED_BUILTIN, LOW);
	delay(50);
}

void receiveEvent(int howMany)
{
	while (0 < Wire.available())
	{
		option = Wire.read();
	}
	isRunning = true;
}

void requestEvent()
{
	char result[2] = { isRunning ? 0 : 1, lastRunResult };
	Wire.write(result);
}
