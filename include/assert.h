#ifndef LUMAOS_ASSERT_H_
#define LUMAOS_ASSERT_H_

#pragma once

#include <panic.h>

#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

#endif