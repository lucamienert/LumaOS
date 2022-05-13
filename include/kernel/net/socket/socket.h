#ifndef LUMAOS_SOCKET_SOCKET_H_
#define LUMAOS_SOCKET_SOCKET_H_

#pragma once

#include <stdint.h>

#define AF_UNIX 1
#define SOCK_STREAM 2
#define SOCK_DGRAM 3

typedef int32_t sa_family_t;
typedef int32_t socklen_t;

struct sockaddr
{
    sa_family_t sa_family;
    char sa_data[4];
};

int32_t socket(int32_t domain, int32_t type, int32_t protocol);
int32_t bind(int32_t soc, const struct sockaddr *addr, socklen_t addrlen);
int32_t listen(int32_t soc, int32_t backlog);
int32_t accept(int32_t soc, struct sockaddr *addr, socklen_t *addrlen);
int32_t send(int32_t soc, const void *buf, size_t len, int32_t flags);
int32_t recv(int32_t soc, void *buf, size_t len, int32_t flags);
int32_t connect(int32_t soc, const struct sockaddr *sock, socklen_t addrlen);


#endif