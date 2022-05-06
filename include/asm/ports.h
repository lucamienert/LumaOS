#ifndef LUMAOS_PORTS_H_
#define LUMAOS_PORTS_H_

#pragma once

#define port_byte_in(port) ({ \
    unsigned char _result; \
    __asm__ volatile("in %%dx, %%al" : "=a" (_result) : "d" (port)); \
   return _result; \
})

#define port_byte_out(port, data) ({ \
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port)); \
})

#define port_word_in(port) ({ \
    unsigned short _result; \
    asm("in %%dx, %%ax" : "=a" (_result) : "d" (port)); \
    return _result; \
})

#define port_word_out(port, data) ({ \
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port)); \
})

#endif