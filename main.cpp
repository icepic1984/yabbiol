#define GPIO0 0x44E07000
#define GPIO1 0x4804C000
#define GPIO2 0x481AC000
#define GPIO3 0x481AE000
#define GPIO_SIZE  0x00000FFF

// #define GPIO_CLEARDATAOUT 0x64
// #define GPIO_SETDATAOUT 0x65
// #define GPIO_DIRECTION 0x4d

#define GPIO_CLEARDATAOUT 0x190 / 4
#define GPIO_SETDATAOUT 0x194 /4
#define GPIO_DIRECTION 0x134 /4
#define GPIO_IN 0x138 /4


#define USR1_LED (1<<30)
#define BUTTON ( 1 <<3)
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[]) {
	volatile unsigned int *gpio_addr = NULL;

    int fd = open("/dev/mem", O_RDWR);
    printf("Mapping %X - %X (size: %X)\n", GPIO1, GPIO0+GPIO_SIZE, GPIO_SIZE);
    gpio_addr = (volatile unsigned int*)mmap(0, GPIO_SIZE, PROT_READ | PROT_WRITE,
                     MAP_SHARED, fd, GPIO0);

    unsigned int reg = *(gpio_addr + GPIO_DIRECTION);
    // reg = reg & (BUTTON);
    // *(gpio_addr + GPIO_DIRECTION) = reg;
    reg = reg & (~(1 << 30));
    
   *(gpio_addr + GPIO_DIRECTION) = reg;

    std::cout << reg << std::endl;
    if(gpio_addr == MAP_FAILED) {
        printf("Unable to map GPIO\n");
        exit(1);
    }
    while(1) {
	    //int read = *(gpio_addr + GPIO_IN) >> 3;
	    // std::cout << read << std::endl;
	    // printf("ON\n");
	    *(gpio_addr + GPIO_SETDATAOUT) = (1 <<30 );
	     sleep(1);
	     printf("OFF\n");
	     *(gpio_addr + GPIO_CLEARDATAOUT) = (1<< 30);
          sleep(1);
    }
    
    close(fd);
    return 0;
}
