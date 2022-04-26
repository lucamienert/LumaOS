#ifndef LUMAOS_TIMER_H_
#define LUMAOS_TIMER_H_

#pragma once

#include "../libc/stdint.h"

#define HZ 1193180

void init_timer(uint32 frequency);

#endif