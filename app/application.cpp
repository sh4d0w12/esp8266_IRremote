#include <user_config.h>
#include "IRremote.h"
#include "IRremoteInt.h"
#include <SmingCore/SmingCore.h>

#define IRR_PIN 12 // GPIO12
#define IRS_PIN 14 // GPIO14

Timer irTimer;
decode_results dresults;
IRrecv irrecv(IRR_PIN);
IRsend irsend(IRS_PIN);

void receiveIR()
{
	if(irrecv.decode(&dresults)==DECODED){
		irTimer.stop();
		unsigned int * sendbuff = new unsigned int[dresults.rawlen-1];
		for(int i=0; i<dresults.rawlen-1; i++){
			sendbuff[i]=dresults.rawbuf[i+1]*50;
		}
		irsend.sendNEC(dresults.value, dresults.bits);
		Serial.println("Sent NEC");
		irrecv.enableIRIn();
		irTimer.start();
	}
	irsend.sendSAMSUNG(0xE0E040BF, 32); // on/off
}

void init()
{
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.println("Setting up...");
	irrecv.blink13(1); // GPIO2
	irrecv.enableIRIn(); // Start the receiver
	irTimer.initializeMs(2000, receiveIR).start();
	Serial.println("Ready...");
}
