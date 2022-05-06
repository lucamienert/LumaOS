#ifndef LUMAOS_TIMER_H_
#define LUMAOS_TIMER_H_

#pragma once

#include <asm/ports.h>
#include <kernel/task.h>
#include <stdint.h>
#include <system/misc.h>

#define HZ 1193180

void init_timer(uint32_t frequency);

#endif