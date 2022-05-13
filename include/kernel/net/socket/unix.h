#ifndef LUMAOS_SOCKET_UNIX_H_
#define LUMAOS_SOCKET_UNIX_H_

#pragma once

#include <stdint.h>
#include <kernel/net/socket_addr.h>

struct socket_conn;
struct socket_conn *unix_socket(int32_t type, int32_t protocol);

#endif