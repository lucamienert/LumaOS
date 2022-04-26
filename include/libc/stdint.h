#ifndef LUMAOS_STDINT_H_
#define LUMAOS_STDINT_H_

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef signed char int8;
typedef short int int16;
typedef int int32;
typedef long int int64;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long int uint64;

typedef float float32;
typedef double float64;

typedef uint32 size_t;

#ifdef __cplusplus
}
#endif

#endif