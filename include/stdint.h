#ifndef LUMAOS_STDINT_H_
#define LUMAOS_STDINT_H_

#pragma once

typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;

#ifndef _SIZE_T
#define _SIZE_T
typedef uint64_t size_t;
#endif

#endif