#ifndef LUMAOS_ARM_SERIAL_H_
#define LUMAOS_ARM_SERIAL_H_

#pragma once

#include <drivers/display.h>
#include <drivers/pl110.h>

#define SERIAL_BASE 0x16000000
#define SERIAL_FLAG_REGISTER 0x18
#define SERIAL_BUFFER_FULL (1 << 5)

void serial_put(char c);
void serial_init();

#endif