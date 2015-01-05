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
		mmap(0, GPIO_SIZE, PROT_READ | PROT_WRITE,
		     MAP_SHARED, fd.m_fd, offset));
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


PinHandle::PinHandle()
{
	m_banks.emplace_back(MemoryHandle(detail::GPIO0));
	m_banks.emplace_back(MemoryHandle(detail::GPIO1));
	m_banks.emplace_back(MemoryHandle(detail::GPIO2));
	m_banks.emplace_back(MemoryHandle(detail::GPIO3));
}

void PinHandle::digitalWrite(Bank bank, unsigned int pin, Value value)
{
	switch(value){
	case Value::LOW:
		m_banks[static_cast<int>(bank)][GPIO_CLEARDATAOUT] = (1 << pin);
		break;
	case Value::HIGH:
		m_banks[static_cast<int>(bank)][GPIO_SETDATAOUT] = (1 << pin);
		break;
	}
}	

Value PinHandle::digitalRead(Bank bank, unsigned int pin)
{
	unsigned int value = (m_banks[static_cast<int>(bank)][GPIO_IN] >> pin);
	if(value == 0){
		return Value::LOW;
	} else {
		return Value::HIGH;
	}

}
	
void PinHandle::pinMode(Bank bank, unsigned int pin, Mode mode)
{
	volatile std::size_t reg = m_banks[static_cast<int>(bank)][GPIO_DIRECTION];
	switch(mode) {
	case Mode::OUTPUT:
		reg = reg & (~(1 << pin));
		break;
	case Mode::INPUT:
		reg = reg & (1 << pin);
		break;
	}	
	m_banks[static_cast<int>(bank)][GPIO_DIRECTION] = reg;
}


PinHandle& getPinHandle()
{
	static PinHandle pinHandle;
	return pinHandle;
}

}
}
