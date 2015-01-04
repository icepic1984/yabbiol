#include <iostream>
#include "gpio.hpp"
#include <unistd.h>

int main(int argc, char *argv[])
{
	using namespace yabbiol;
	// yabbiol::detail::PinHandle bla;
	pinMode(Bank::GPIO0,30,yabbiol::Mode::OUTPUT);
	pinMode(Bank::GPIO0,3,yabbiol::Mode::INPUT);

	digitalWrite(Bank::GPIO0,30,yabbiol::Value::HIGH);
	sleep(1);
	digitalWrite(yabbiol::Bank::GPIO0,30,yabbiol::Value::LOW);

	while(digitalRead(Bank::GPIO0,3) != Value::HIGH){
		std::cout << "HAHA" << std::endl;
	}
	
	return 0;
}
