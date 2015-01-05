#ifndef GPIO_HPP
#define GPIO_HPP

#include "util.hpp"

namespace yabbiol {

void init();
void pinMode(Bank bank, unsigned int pin, Mode mode);
void digitalWrite(Bank bank, unsigned int pin, Value value);
Value digitalRead(Bank bank, unsigned int pin);
void delayMicroseconds(unsigned int us);
void delay(unsigned int ms);
auto micro() -> decltype(std::chrono::time_point_cast<Us>(Clock::now()));
auto milli() -> decltype(std::chrono::time_point_cast<Ms>(Clock::now())) ;
auto nano() -> decltype(std::chrono::time_point_cast<Ns>(Clock::now())) ;

}

#endif
