#ifndef UTIL_HPP
#define UTIL_HPP
#include <cstdlib>
#include <string>

namespace yabbiol {

enum class Mode {INPUT, OUTPUT};
enum class Value {LOW, HIGH};
enum class Bank {GPIO0,GPIO1,GPIO2,GPIO3};

namespace detail {


const size_t GPIO0 = 0x44E07000;
const size_t GPIO1 = 0x4804C000;
const size_t GPIO2 = 0x481AC000;
const size_t GPIO3 = 0x481AE000;
const size_t GPIO_SIZE = 0x00000FFF;
const size_t GPIO_CLEARDATAOUT = 0x190 / 4;
const size_t GPIO_SETDATAOUT = 0x194 /4;
const size_t GPIO_DIRECTION = 0x134 /4;
const size_t GPIO_IN = 0x138 /4;

const std::string MEM_FILE("/dev/mem");

class FileHandle
{
public:
   FileHandle();
   ~FileHandle();

   FileHandle( const FileHandle& ) = delete;
   FileHandle& operator=(const FileHandle&) = delete;

   FileHandle(FileHandle&& other);
   FileHandle& operator=(FileHandle&& other);

   int m_fd;
};


class MemoryHandle
{
public:
   MemoryHandle(std::size_t offset);
   ~MemoryHandle();

   MemoryHandle(const MemoryHandle&) = delete;
   MemoryHandle& operator=(const MemoryHandle&) = delete;
   MemoryHandle(MemoryHandle&& other);
   MemoryHandle& operator=(MemoryHandle&& other);

   volatile std::size_t& operator[](std::size_t offset);
   volatile std::size_t operator[](std::size_t offset) const;

   
private:
   volatile std::size_t* m_addrspace = nullptr;
};

class PinHandle 
{
public:
   PinHandle(const PinHandle&) = delete;
   PinHandle& operator=(const PinHandle&) = delete;
   PinHandle(PinHandle&&) = default;
   PinHandle& operator=(PinHandle&&) = default;

   void pinMode(Bank bank, unsigned int pin, Mode mode);
   void digitalWrite(Bank bank, unsigned int pin, Value value);
   Value digitalRead(Bank bank, unsigned int pin);
   
   friend PinHandle& getPinHandle();
   
private:
   PinHandle();
   void pinMode(MemoryHandle& handle, unsigned int pin, Mode mode);
   void digitalWrite(MemoryHandle& handle, unsigned int pin, Value value);
   Value digitalRead(MemoryHandle& handle, unsigned int pin);
   
   MemoryHandle m_gpio0;
   MemoryHandle m_gpio1;
   MemoryHandle m_gpio2;
   MemoryHandle m_gpio3;
};

PinHandle& getPinHandle();

}
}

#endif
