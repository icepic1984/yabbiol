#ifndef RCSWITCH_HPP
#define RCSWITCH_HPP

#include "gpio.hpp"
#include <string>

namespace yarcs {

static const unsigned int pulseLength = 350;
static const unsigned int repeatTransmit = 10;

class RcSwitch 
{
public:
   RcSwitch(yabbiol::Bank bank, unsigned pin,
            const std::string& group,
            const std::string& device);
   void switchOn();
   void switchOff();
private:
   void sendT0();
   void sendT1();
   void sendTF();
   void sendSync();
   void transmit(int highPulse, int lowPulse);
   void sendTelegram(const std::string& telegram);
   
   std::string getTelegram(const std::string& group,
                           const std::string& device, bool on);
   
   yabbiol::Bank m_bank;
   unsigned int m_pin;
   std::string m_group;
   std::string m_device;
   std::string m_telegram_on;
   std::string m_telegram_off;
};

}

#endif
