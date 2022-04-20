#ifndef LMOS_PORTS_H_
#define LMOS_PORTS_H_

#pragma once

#include "../utils/types.h"

uint8 port_byte_in(uint16 port);
void port_byte_out(uint16 port, uint8 data);

uint16 port_word_in(uint16 port);
void port_word_out(uint16 port, uint16 data);

#endif