#include"kernel.h"  
  
static uint16 VGA_DefaultEntry(unsigned char to_print) {  
    return (uint16) to_print | (uint16)WHITE_COLOR << 8;  
}  

void print(char *str)  
{  
    uint32 index = 0;  
    while(str[index]){  
        TERMINAL_BUFFER[VGA_INDEX] = VGA_DefaultEntry(str[index]);  
        ++index;  
        ++VGA_INDEX;  
    }  
}  

void KERNEL_MAIN()  
{  
    TERMINAL_BUFFER = (uint16*) VGA_ADDRESS;  
    print("Hello World!");
}   
