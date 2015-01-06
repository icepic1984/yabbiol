#include "gpio.hpp"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <cstdint>
#include <sched.h>
#include <string.h>

void set_max_priority(void) {
	struct sched_param sched;
	memset(&sched, 0, sizeof(sched));
	sched.sched_priority = sched_get_priority_max(SCHED_FIFO);
	sched_setscheduler(0, SCHED_FIFO, &sched);
}
void set_default_priority(void) {
	struct sched_param sched;
	memset(&sched, 0, sizeof(sched));
	sched.sched_priority = 0;
	sched_setscheduler(0, SCHED_OTHER, &sched);
}
int main(int argc, char *argv[])
{
	using namespace yabbiol;
	// yabbiol::detail::PinHandle bla;

	int pin = 16;
	uint8_t mask = 128;
	uint8_t idx = 0;
	//std::vector<int> counter(40);

	
	uint8_t data[5];
	for (size_t i = 0; i < 5; ++i){
		data[i] = 0;
	}

	Value last = yabbiol::Value::HIGH;
	set_max_priority();
	
	pinMode(Bank::GPIO1,pin,yabbiol::Mode::OUTPUT);
	digitalWrite(yabbiol::Bank::GPIO1,pin,yabbiol::Value::LOW);
	delay(1);
	digitalWrite(yabbiol::Bank::GPIO1,pin,yabbiol::Value::HIGH);
	delayMicroseconds(20);
	pinMode(Bank::GPIO1,pin,yabbiol::Mode::INPUT);
	while(digitalRead(Bank::GPIO1,pin) == Value::LOW){}
	while(digitalRead(Bank::GPIO1,pin) == Value::HIGH){}

	for ( uint8_t i = 0; i < 40; i++ ) {
		int counter = 0;
		while (digitalRead(Bank::GPIO1,pin) == Value::LOW) {}
		while (digitalRead(Bank::GPIO1,pin) == Value::HIGH) {
			counter++;
		}

		if ( counter > 200 ) data[idx] |= mask;
		mask >>= 1;
		if ( mask == 0 ) {
			mask = 128;
			idx++;
		}
	}
	set_default_priority();

	uint8_t sum = data[0] + data[1] + data[2] + data[3];
	float temperature;
	float humidity;
	std::cout << sum << std::endl;
	if ( sum == data[4]) {
		uint16_t t_hum = data[0];
		t_hum <<= 8;
		t_hum |= data[1];
		humidity = static_cast<float>(t_hum) * 0.1f;

		if( data[2] & 128) {
			uint16_t t_temp = data[2] & 127;
			t_temp <<= 8;
			t_temp |= data[3];
			temperature = -0.1f * static_cast<float>(t_temp);
		} else {
			uint16_t t_temp = data[2];
			t_temp <<= 8;
			t_temp |= data[3];
			temperature = static_cast<float>(t_temp) * 0.1f;
		}
		std::cout << "Hum: "<<humidity<<" Temp: "<<temperature << std::endl;
	} else {
		std::cout << "FUCK"<< std::endl;
	}
	return 0;
}
