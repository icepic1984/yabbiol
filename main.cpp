#include "gpio.hpp"
#include "rcswitch.hpp"
#include <iostream>

int main(int argc, char *argv[]) 
{
	using namespace yarcs;
	using namespace yabbiol;

	std::vector<std::string> params(argv+1, argv+argc);
	if(params.size() != 3){
		std::cerr <<"Not enough parameters"<<std::endl;
		return -1;
	}

	RcSwitch rcs(Bank::GPIO0,30,params[0],params[1]);
	if(params[2] == "1"){
	   rcs.switchOn();
	} else if(params[2] == "0") {
	   rcs.switchOff();
	} else {
	   std::cerr<<"Invalid Switch command!"<<std::endl;
	   return -1;
	}
	return 0;
}
