#include "gpio.hpp"
#include "rcswitch.hpp"
#include <iostream>

static const unsigned int pulseLength = 350;
static const unsigned int repeatTransmit = 10;
static const int pin = 30;

using namespace yabbiol;

void transmit(int nHigh, int nLow) 
{
	digitalWrite(yabbiol::Bank::GPIO0,pin,yabbiol::Value::HIGH);
	delayMicroseconds(pulseLength * nHigh);
	digitalWrite(yabbiol::Bank::GPIO0,pin,yabbiol::Value::LOW);
	delayMicroseconds(pulseLength * nLow);
}

void sendT0()
{
	transmit(1,3);
	transmit(1,3);
}

void sendTF() {
	transmit(1,3);
	transmit(3,1);
}

void sendT1()
{
	transmit(3,1);
	transmit(3,1);
}

void sendSync() 
{transmit(1,31);}

char* getCodeWordA(char* sGroup, char* sDevice, bool bOn) {
    static char sDipSwitches[13];
    int i = 0;
    int j = 0;
    
    for (i=0; i < 5; i++) {
        if (sGroup[i] == '0') {
            sDipSwitches[j++] = 'F';
        } else {
            sDipSwitches[j++] = '0';
        }
    }
    for (i=0; i < 5; i++) {
        if (sDevice[i] == '0') {
            sDipSwitches[j++] = 'F';
        } else {
            sDipSwitches[j++] = '0';
        }
    }
    if ( bOn ) {
        sDipSwitches[j++] = '0';
        sDipSwitches[j++] = 'F';
    } else {
        sDipSwitches[j++] = 'F';
        sDipSwitches[j++] = '0';
    }
    sDipSwitches[j] = '\0';
    return sDipSwitches;
}


void sendTriState(char* sCodeWord) {
  for (int nRepeat = 0; nRepeat < repeatTransmit; nRepeat++) {
    int i = 0;
    while (sCodeWord[i] != '\0') {
      switch(sCodeWord[i]) {
        case '0':
          sendT0();
        break;
        case 'F':
          sendTF();
        break;
        case '1':
          sendT1();
        break;
      }
      i++;
    }
    sendSync();    
  }
}

int main(int argc, char *argv[]) 
{
	yarcs::RcSwitch rcs(Bank::GPIO0,pin,"11111","01000");
	rcs.switchOn();
	
	
	// int pin = 30;
	// digitalWrite(yabbiol::Bank::GPIO0,pin,yabbiol::Value::LOW);
	// delay(1);
	// for(int i = 0; i < 100; ++i){
	// 	digitalWrite(yabbiol::Bank::GPIO0,pin,yabbiol::Value::LOW);
	// 	delay(100);
	// 	digitalWrite(yabbiol::Bank::GPIO0,pin,yabbiol::Value::HIGH);	
	// }	
		

}
