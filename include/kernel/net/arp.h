#ifndef LUMAOS_ARP_H_
#define LUMAOS_ARP_H_

#pragma once

#include <stdint.h>

#define ARP_HTYPE_ETHERNET 1
#define ARP_PTYPE_IPV4 0x800
#define ARP_PTYPE_IPV6 0x806
#define ARP_REQUEST 1
#define ARP_REPLY 2

typedef struct ArpFrame
{
    uint16_t htype;
    uint16_t ptype;
    uint8_t  hlen;
    uint8_t  plen;
    uint16_t operation;
    uint8_t  source_mac[6];
    uint32_t source_paddr;
    uint8_t  target_mac[6];
    uint32_t target_paddr
} arp_frame_t;

#endif