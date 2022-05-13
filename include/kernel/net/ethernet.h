#ifndef LUMAOS_ETHERNET_H_
#define LUMAOS_ETHERNET_H_

#pragma once

#include <stdint.h>

#define ETHER_TYPE_IPV4 0x0800
#define ETHER_TYPE_ARP  0x0806
#define ETHER_TYPE_IPV6 0x86DD

#define ETHERNET_LAYER_SIZE sizeof(ethernet_frame_t) + 4 

typedef struct EthernetFrame
{
    uint8_t dest_mac[6];
    uint8_t source_mac[6];
    uint16_t type;
    uint8_t payload;
} ethernet_frame_t;

#endif