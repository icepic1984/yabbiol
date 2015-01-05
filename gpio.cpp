#include "gpio.hpp"
#include <chrono>
#include <thread>

namespace yabbiol {

void init()
{detail::getPinHandle();}

void pinMode(Bank bank, unsigned int pin, Mode mode)
{detail::getPinHandle().pinMode(bank,pin,mode);}
	
void digitalWrite(Bank bank, unsigned int pin, Value value)
{detail::getPinHandle().digitalWrite(bank,pin,value);}

Value digitalRead(Bank bank, unsigned int pin)
{return detail::getPinHandle().digitalRead(bank,pin);}

void delayMicroseconds(unsigned int us)
{std::this_thread::sleep_for(std::chrono::microseconds(us));}

void delay(unsigned int ms)
{std::this_thread::sleep_for(std::chrono::milliseconds(ms));}

auto micro() -> decltype(std::chrono::time_point_cast<Us>(Clock::now()))
{return std::chrono::time_point_cast<Us>(Clock::now());}

auto milli() -> decltype(std::chrono::time_point_cast<Ms>(Clock::now())) 
{return std::chrono::time_point_cast<Ms>(Clock::now());}

auto nano() -> decltype(std::chrono::time_point_cast<Ns>(Clock::now()))
{return std::chrono::time_point_cast<Ns>(Clock::now());}

}

