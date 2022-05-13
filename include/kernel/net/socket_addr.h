#ifndef LUMAOS_SOCKET_ADDR_H_
#define LUMAOS_SOCKET_ADDR_H_

#pragma once

#include <stdint.h>

#define SOC_PATH_LENGTH 108

struct sockaddr_un
{
    int32_t sun_family;
    char sun_path[SOC_PATH_LENGTH];
};

#endif