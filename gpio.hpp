#ifndef GPIO_HPP
#define GPIO_HPP

#include "util.hpp"

namespace yabbiol {

void pinMode(unsigned int port, unsigned int pin, Mode mode);
void digitalWrite(unsigned int port, unsigned int pin, Value value);
Value digitalRead(unsigned int port, unsigned int pin);
}

#endif
