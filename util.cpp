#include "util.hpp"
#include <string>
#include <stdexcept>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

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

PinHandle::PinHandle():
	m_gpio0(detail::GPIO0),
	m_gpio1(detail::GPIO1),
	m_gpio2(detail::GPIO2),
	m_gpio3(detail::GPIO3)
{}


void PinHandle::setDirection(Bank bank, unsigned int pin, Mode mode)
{
	switch(bank){
	case Bank::GPIO0:
		break;
	case Bank::GPIO1:
		break;
	case Bank::GPIO2:
		break;
	case Bank::GPIO3:
		break;
	}
		
	  



}
}
