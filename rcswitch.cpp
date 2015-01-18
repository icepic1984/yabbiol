#include "rcswitch.hpp"
#include <stdexcept>
#include <iostream>


namespace yarcs {

RcSwitch::RcSwitch(yabbiol::Bank bank,
                   unsigned int pin,
                   const std::string& group,
                   const std::string& device) :
	m_bank(bank),
	m_pin(pin),
	m_group(group),
	m_device(device)
{
	m_telegram_on = getTelegram(m_group,m_device,true);
	m_telegram_off = getTelegram(m_group,m_device,false);
}

void RcSwitch::sendT0()
{
	transmit(1,3);
	transmit(1,3);
}

void RcSwitch::sendT1()
{
	transmit(3,1);
	transmit(3,1);
}

void RcSwitch::sendTF()
{
	transmit(1,3);
	transmit(3,1);
}

void RcSwitch::sendSync() 
{transmit(1,31);}

void RcSwitch::transmit(int highPulse, int lowPulse)
{
	yabbiol::digitalWrite(m_bank,m_pin,yabbiol::Value::HIGH);
	yabbiol::delayMicroseconds(pulseLength * highPulse);
	yabbiol::digitalWrite(m_bank,m_pin,yabbiol::Value::LOW);
	yabbiol::delayMicroseconds(pulseLength * lowPulse);
}

std::string RcSwitch::getTelegram(const std::string& group,
                                    const std::string& device, bool on)
{
	if((group.size() != 5) || (device.size() != 5)){
		throw std::runtime_error("Invalid rc device: " + group + " " + device);
	}
	for(const char& c : group){
		if((c != '0') && (c != '1')){
			throw std::runtime_error("Invalid rc device: " + group + " " + device);	
		}
	}
	for(const char& c : device){
		if((c != '0') && (c != '1')){
			throw std::runtime_error("Invalid rc device: " + group + " " + device);	
		}
	}
	
	std::string telegram(12,'0');
	
	int j = 0;
	for (int i = 0; i < 5; i++) {
		if (group[i] == '0') {
			telegram[j++] = 'F';
        } else {
            telegram[j++] = '0';
        }
    }
    for (int i = 0; i < 5; i++) {
        if (device[i] == '0') {
            telegram[j++] = 'F';
        } else {
            telegram[j++] = '0';
        }
    }
    if (on) {
        telegram[j++] = '0';
        telegram[j++] = 'F';
    } else {
        telegram[j++] = 'F';
        telegram[j++] = '0';
    }
    return telegram;
}

void RcSwitch::switchOn()
{sendTelegram(m_telegram_on);}

void RcSwitch::switchOff()
{sendTelegram(m_telegram_off);}

void RcSwitch::sendTelegram(const std::string& telegram) {
  for (int i = 0; i < repeatTransmit; ++i) {
	  for(const char& c : telegram){
		  switch(c){
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
	  }
	  sendSync();    
  }
}


}

 
