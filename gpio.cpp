#include "gpio.hpp"

namespace yabbiol {

void initIO()
{
	detail::getPinHandle();
}

void pinMode(Bank bank, unsigned int pin, Mode mode)
{
	detail::getPinHandle().pinMode(bank,pin,mode);
}
	
void digitalWrite(Bank bank, unsigned int pin, Value value)
{
	detail::getPinHandle().digitalWrite(bank,pin,value);
}

Value digitalRead(Bank bank, unsigned int pin)
{
	return detail::getPinHandle().digitalRead(bank,pin);
}

}

