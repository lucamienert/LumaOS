#include"kernel.h"  
  
static UINT16 VGA_DefaultEntry(unsigned char to_print) {  
    return (UINT16) to_print | (UINT16)WHITE_COLOR << 8;  
}  

void printString(char *str)  
{  
  int index = 0;  
  while(str[index]){  
    TERMINAL_BUFFER[VGA_INDEX] = VGA_DefaultEntry(str[index]);  
    index++;  
    VGA_INDEX++;  
  }  
}  

void KERNEL_MAIN()  
{  
  TERMINAL_BUFFER = (UINT16*) VGA_ADDRESS;  
  printString("Hello World!");
}   
