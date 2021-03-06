
#include "pwm.h"

int  mem_fd;
void *gpio_map;
volatile unsigned *gpio;
 

volatile unsigned*  setup_io()
{
   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }
 
   /* mmap GPIO */
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );
 
   close(mem_fd); //No need to keep mem_fd open after mmap
 
   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }
 
   // Always use volatile pointer!
   return gpio = (volatile unsigned *)gpio_map;
  
} // setup_iovoid setup_io()


void init_Gpio_Out(int voix){
   OUT_GPIO( voix );
}

void init_Gpio_In(int voix){
   INP_GPIO( voix );   
}

//value 1 or 0
void gpio_set(int value, int voix){
    GPIO_SET = value << voix;
}

void gpio_clr(int value, int voix){
   GPIO_CLR = value << voix;
}

