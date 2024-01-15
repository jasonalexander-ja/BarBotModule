#include <Arduino.h>
#include <Wire.h>
#include <Unit.h>


/*
This is just utility setup code for communicating with the controller ext.

For programming your module please edit `Unit.cpp` in the `lib/Unit` folder, 
and ignore this file. 
*/


uint8_t option = 0;
bool concurrentLock = false;

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
	delay(100);
	digitalWrite(LED_BUILTIN, LOW);
	delay(100);
}

void receiveEvent(int howMany)
{
	while (1 < Wire.available())
	{
		uint8_t c = Wire.read();
	}
	option = Wire.read();
}

void requestEvent()
{
	if (concurrentLock)
		return;
	concurrentLock = true;

	digitalWrite(LED_BUILTIN, HIGH);

	uint8_t result = performAction(option);

	digitalWrite(LED_BUILTIN, LOW);

	Wire.write(result);
	concurrentLock = false;
}
