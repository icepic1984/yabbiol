#ifndef GPIO_HPP
#define GPIO_HPP

#include "util.hpp"

namespace yabbiol {

void initIO();
void pinMode(Bank bank, unsigned int pin, Mode mode);
void digitalWrite(Bank bank, unsigned int pin, Value value);
Value digitalRead(Bank bank, unsigned int pin);

}

#endif
