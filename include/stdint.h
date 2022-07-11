#ifndef LUMAOS_STDINT_H_
#define LUMAOS_STDINT_H_

#pragma once

/* signed */
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;
#ifdef __EXTENDED__
typedef long long int64_t;
#endif

/* unsigned */
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;
#ifdef __EXTENDED__
typedef unsigned long long int64_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef uint64_t size_t;
#endif

/* Defining min and max number that can be represented with each datatype */
#define INT8_MIN -128
#define INT8_MAX 127
#define INT16_MIN -32768
#define INT16_MAX 32767

#endif