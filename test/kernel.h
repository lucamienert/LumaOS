#ifndef _KERNEL_H_  
#define _KERNEL_H_  
  
#define VGA_ADDRESS 0xB8000  
#define WHITE_COLOR 15  
#define BUFSIZE 2200
  
typedef unsigned short uint16;
typedef unsigned short uint32;

uint32 DIGIT_ASCII_CODES[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};  
uint32 VGA_INDEX;  
  
uint16 *TERMINAL_BUFFER;  
  
#endif  