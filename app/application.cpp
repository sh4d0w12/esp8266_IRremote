#include <user_config.h>
#include "IRremote.h"
#include <SmingCore/SmingCore.h>

#define IRR_PIN 5 // GPIO5
#define IRS_PIN 4 // GPIO4
#define LED_PIN 2 // GPIO2

Timer irTimer;
decode_results results;
IRrecv irrecv(IRR_PIN);
IRsend irsend(IRS_PIN);

void dump(decode_results *results)
{
	Serial.print("type: ");
	Serial.print(results->decode_type);
	Serial.print(" hex: 0x");
	Serial.print(results->value, HEX);
	Serial.print(" dec: ");
	Serial.print(results->value, DEC);
	Serial.print(" bits: ");
	Serial.print(results->bits, DEC);
	Serial.println();
}

void loop()
{

	if (irrecv.decode(&results))
	{
		dump(&results);
		irrecv.resume();
		Serial.println("send mute to samsung");
		irsend.sendSAMSUNG(0xE0E0F00F, 32);
	}
	irTimer.startOnce();
}

void init()
{
	System.setCpuFrequency(eCF_160MHz);
	Serial.begin(SERIAL_BAUD_RATE);
	Serial.println("Setting up...");
	irrecv.blink(true, LED_PIN);
	irrecv.enableIRIn();
	irTimer.initializeMs(1000, loop).startOnce();
}
