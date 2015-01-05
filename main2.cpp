#include "gpio.hpp"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <cstdint>

int main(int argc, char *argv[])
{
	using namespace yabbiol;
	// yabbiol::detail::PinHandle bla;

	uint8_t data[4];
	for (size_t i = 0; i < 5; ++i){
		data[i] = 0;
	}

	delay(1000);
	pinMode(Bank::GPIO1,16,yabbiol::Mode::INPUT);
	digitalRead(Bank::GPIO1,16);

	
	
	// pinMode(Bank::GPIO1,16,yabbiol::Mode::OUTPUT);
	// digitalWrite(yabbiol::Bank::GPIO1,16,yabbiol::Value::LOW);

	// pinMode(Bank::GPIO1,16,yabbiol::Mode::OUTPUT);
	// digitalWrite(yabbiol::Bank::GPIO1,16,yabbiol::Value::LOW);
	// delay(10);
	// digitalWrite(yabbiol::Bank::GPIO1,16,yabbiol::Value::HIGH);
	// delayMicroseconds(40);
	// pinMode(Bank::GPIO1,16,yabbiol::Mode::INPUT);

	// int loop_count = 0;
	// while(digitalRead(Bank::GPIO1,16) == Value::LOW){
	// 	loop_count++;
	// }
	// std::cout << loop_count<< std::endl;
	
	
	return 0;
}
