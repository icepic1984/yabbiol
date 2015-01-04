#include "util.hpp"
#include <string>
#include <stdexcept>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

namespace yabbiol {
namespace detail {

FileHandle::FileHandle()
{
	m_fd = open(MEM_FILE.c_str(),O_RDWR);
	if(m_fd == -1)
	   throw std::runtime_error("Could not open " +  std::string(MEM_FILE));
}

FileHandle::~FileHandle()
{
	if(m_fd > -1)
	   close(m_fd);
}

FileHandle::FileHandle(FileHandle&& other)
{
	m_fd = other.m_fd;
	other.m_fd = -1;
}

FileHandle& FileHandle::operator=(FileHandle&& other)
{
	m_fd = other.m_fd;
	other.m_fd = -1;
	return *this;
}

MemoryHandle::MemoryHandle(std::size_t offset)
{
	FileHandle fd;
	m_addrspace = static_cast<std::size_t*>(
		mmap(0, GPIO_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd.m_fd, offset));
	if(m_addrspace == MAP_FAILED)
	   throw std::runtime_error("nmap failed");
}

MemoryHandle::~MemoryHandle()
{
	if(m_addrspace != MAP_FAILED ||
	   m_addrspace != nullptr) {
		munmap(const_cast<std::size_t*>(m_addrspace),GPIO_SIZE);
	}
}

MemoryHandle::MemoryHandle(MemoryHandle&& other)
{
	m_addrspace = other.m_addrspace;
	other.m_addrspace = nullptr;
}

MemoryHandle& MemoryHandle::operator=(MemoryHandle&& other)
{
	m_addrspace = other.m_addrspace;
	other.m_addrspace = nullptr;
	return *this;
}

volatile std::size_t& MemoryHandle::operator[](std::size_t offset)
{
	return *(m_addrspace + offset);
}

volatile std::size_t MemoryHandle::operator[](std::size_t offset) const 
{return *(m_addrspace + offset);}


PinHandle::PinHandle():
	m_gpio0(detail::GPIO0),
	m_gpio1(detail::GPIO1),
	m_gpio2(detail::GPIO2),
	m_gpio3(detail::GPIO3)
{}

void PinHandle::digitalWrite(Bank bank, unsigned int pin, Value value)
{
	switch(bank){
	case Bank::GPIO0:
		digitalWrite(m_gpio0,pin,value);
		break;
	case Bank::GPIO1:
		digitalWrite(m_gpio1,pin,value);
		break;
	case Bank::GPIO2:
		digitalWrite(m_gpio2,pin,value);
		break;
	case Bank::GPIO3:
		digitalWrite(m_gpio3,pin,value);
		break;
	}
}	
Value PinHandle::digitalRead(Bank bank, unsigned int pin)
{
	switch(bank){
	case Bank::GPIO0:
		return digitalRead(m_gpio0,pin);
	case Bank::GPIO1:
		return digitalRead(m_gpio1,pin);
		break;
	case Bank::GPIO2:
		return digitalRead(m_gpio2,pin);
		break;
	case Bank::GPIO3:
		return digitalRead(m_gpio3,pin);
		break;
	}
}

	
void PinHandle::pinMode(Bank bank, unsigned int pin, Mode mode)
{
	switch(bank){
	case Bank::GPIO0:
		pinMode(m_gpio0,pin,mode);
		break;
	case Bank::GPIO1:
		pinMode(m_gpio1,pin,mode);
		break;
	case Bank::GPIO2:
		pinMode(m_gpio2,pin,mode);
		break;
	case Bank::GPIO3:
		pinMode(m_gpio3,pin,mode);
		break;
	}
}
void PinHandle::digitalWrite(MemoryHandle& handle, unsigned int pin, Value value)
{
	switch(value){
	case Value::LOW:
		handle[GPIO_CLEARDATAOUT] = (1 << pin);
		break;
	case Value::HIGH:
		handle[GPIO_SETDATAOUT] = (1 << pin);
		break;
	}
}
	
void PinHandle::pinMode(MemoryHandle& handle,
                             unsigned int pin, Mode mode)
{
	volatile std::size_t reg = handle[GPIO_DIRECTION];
	switch(mode) {
	case Mode::OUTPUT:
		reg = reg & (~(1 << pin));
		break;
	case Mode::INPUT:
		reg = reg & (1 << pin);
		break;
	}	
	handle[GPIO_DIRECTION] = reg;
}

Value PinHandle::digitalRead(MemoryHandle& handle, unsigned int pin)
{
	unsigned int value = (handle[GPIO_IN] >> pin);
	if(value == 0){
		return Value::LOW;
	} else {
		return Value::HIGH;
	}
}

PinHandle& getPinHandle()
{
	static PinHandle pinHandle;
	return pinHandle;
}


}
}
