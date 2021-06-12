/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/*
 * Copyright (c) 2013-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SDRVL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "netif/etharp.h"

#include <stdlib.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

#include "ethernet_.h"

EnetOperations operations;
EthernetIo ethernet_io;

#define ENET_FRAME_MAX_FRAMELEN 1518U /*!< Default maximum Ethernet frame size. */

#define ENET_OK             (0U)
#define ENET_ERROR          (0xFFU)
#define ENET_TIMEOUT        (0xFFFU)

enum _enet_status
{
    kStatus_ENET_RxFrameError = MAKE_STATUS(kStatusGroup_ENET, 0U),   /*!< A frame received but data error happen. */
    kStatus_ENET_RxFrameFail = MAKE_STATUS(kStatusGroup_ENET, 1U),    /*!< Failed to receive a frame. */
    kStatus_ENET_RxFrameEmpty = MAKE_STATUS(kStatusGroup_ENET, 2U),   /*!< No frame arrive. */
    kStatus_ENET_TxFrameOverLen = MAKE_STATUS(kStatusGroup_ENET, 3U), /*!< Tx frame over length. */
    kStatus_ENET_TxFrameBusy = MAKE_STATUS(kStatusGroup_ENET, 4U),    /*!< Tx buffer descriptors are under process. */
    kStatus_ENET_TxFrameFail = MAKE_STATUS(kStatusGroup_ENET, 5U)     /*!< Transmit frame fail. */
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
    ,
    kStatus_ENET_PtpTsRingFull = MAKE_STATUS(kStatusGroup_ENET, 6U), /*!< Timestamp ring full. */
    kStatus_ENET_PtpTsRingEmpty = MAKE_STATUS(kStatusGroup_ENET, 7U) /*!< Timestamp ring empty. */
#endif                                                               /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
};

#define ENET_ATONEGOTIATION_TIMEOUT     (0xFFFU)

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become available since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t low_level_output(struct netif *netif, struct pbuf *p) {
err_t result;
struct pbuf *q;
unsigned char *pucBuffer;
unsigned char *pucChar;
static unsigned char ucBuffer[ENET_FRAME_MAX_FRAMELEN];
pucBuffer = ucBuffer;
if (pucBuffer == NULL) {
	return ERR_BUF;
}

/* Initiate transfer. */

#if ETH_PAD_SIZE
pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

if (p->len == p->tot_len) {
#if defined(FSL_FEATURE_SOC_ENET_COUNT) && (FSL_FEATURE_SOC_ENET_COUNT > 0)
	/* No pbuf chain, don't have to copy -> faster. */
	pucBuffer = (unsigned char *) p->payload;
#elif defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
	/* No pbuf chain, still have to copy as pbuf could be reclaimed early. */
	memcpy(pucBuffer, p->payload, p->len);
#endif /* FSL_FEATURE_SOC_*_ENET_COUNT */
} else {
	/* pbuf chain, copy into contiguous ucBuffer. */
	if (p->tot_len >= ENET_FRAME_MAX_FRAMELEN) {
		return ERR_BUF;
	} else {
		pucChar = pucBuffer;

		for (q = p; q != NULL; q = q->next) {
			/* Send the data from the pbuf to the interface, one pbuf at a
			 time. The size of the data in each pbuf is kept in the ->len
			 variable. */
			/* send data from(q->payload, q->len); */
			memcpy(pucChar, q->payload, q->len);
			pucChar += q->len;
		}
	}
}

uint32_t counter;
/* Send frame. */
result = ERR_TIMEOUT;
for (counter = ENET_TIMEOUT; counter != 0U; counter--) {
   if (ethernet_io.send_tx_frame(pucBuffer, p->tot_len)     != kStatus_ENET_TxFrameBusy) {
      result = ERR_OK;
      break;
   }
}

MIB2_STATS_NETIF_ADD(netif, ifoutoctets, p->tot_len);
if (((u8_t *) p->payload)[0] & 1) {
	/* broadcast or multicast packet*/
} else {
	/* unicast packet */
}
/* increase ifoutdiscards or ifouterrors on error */

#if ETH_PAD_SIZE
pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

LINK_STATS_INC(link.xmit);

return result;
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *low_level_input(struct netif * bb) {
struct pbuf *p = NULL;
struct pbuf *q;
uint32_t len;
status_t status;
/* Obtain the size of the packet and put it into the "len"
 variable. */
status = ethernet_io.get_rx_frame_size(&len);
if (kStatus_ENET_RxFrameEmpty != status) {
	/* Call enet_read_frame when there is a received frame. */
	if (len != 0) {
#if ETH_PAD_SIZE
		len += ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

		/* We allocate a pbuf chain of pbufs from the pool. */
		p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

		if (p != NULL) {
#if ETH_PAD_SIZE
			pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif
			if (p->next == 0) /* One-chain buffer.*/
			{
				ethernet_io.read_rx_frame(p->payload, p->len);
			} else /* Multi-chain buffer.*/
			{
				uint8_t data_tmp[ENET_FRAME_MAX_FRAMELEN];
				uint32_t data_tmp_len = 0;

				ethernet_io.read_rx_frame(data_tmp, p->tot_len);

				/* We iterate over the pbuf chain until we have read the entire
				 * packet into the pbuf. */
				for (q = p;
						(q != NULL)
								&& ((data_tmp_len + q->len) <= sizeof(data_tmp));
						q = q->next) {
					/* Read enough bytes to fill this pbuf in the chain. The
					 * available data in the pbuf is given by the q->len
					 * variable. */
					memcpy(q->payload, &data_tmp[data_tmp_len], q->len);
					data_tmp_len += q->len;
				}
			}

			if (((u8_t *) p->payload)[0] & 1) {
				/* broadcast or multicast packet*/
			} else {
				/* unicast packet*/
			}
#if ETH_PAD_SIZE
			pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

		} else {
			/* drop packet*/
			ethernet_io.read_rx_frame(NULL, 0U);
		}
	} else {
		/* Update the received buffer when error happened. */
		if (status == kStatus_ENET_RxFrameError) {
			/* Update the receive buffer. */
			ethernet_io.read_rx_frame(NULL, 0U);
		}
	}
}
return p;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
void ethernetif_input(struct netif *netif) {
struct pbuf *p;

LWIP_ASSERT("netif != NULL", (netif != NULL));

/* move received packet into a new pbuf */
while ((p = low_level_input(netif)) != NULL) {
	/* pass all packets to ethernet_input, which decides what packets it supports */
	if (netif->input(p, netif) != ERR_OK) {
		LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
		pbuf_free(p);
		p = NULL;
	}
}
}

/**
 * Should be called at the beginning of the program to set up the
 * first network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t ethernetif0_init(struct netif *netif) {
GetEnetOperations(&operations);

#if LWIP_NETIF_HOSTNAME
/* Initialize interface hostname */
netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

netif->name[0] = IFNAME0;
netif->name[1] = IFNAME1;
/* We directly use etharp_output() here to save a function call.
 * You can instead declare your own function an call etharp_output()
 * from it if you have to do some checks before sending (e.g. if link
 * is available...) */
#if LWIP_IPV4
netif->output = etharp_output;
#endif
#if LWIP_IPV6
netif->output_ip6 = ethip6_output;
#endif /* LWIP_IPV6 */
netif->linkoutput = low_level_output;

#if LWIP_IPV4 && LWIP_IGMP
netif_set_igmp_mac_filter(netif, ethernetif_igmp_mac_filter);
netif->flags |= NETIF_FLAG_IGMP;
#endif
#if LWIP_IPV6 && LWIP_IPV6_MLD
netif_set_mld_mac_filter(netif, ethernetif_mld_mac_filter);
netif->flags |= NETIF_FLAG_MLD6;
#endif

/* set MAC hardware address length */
netif->hwaddr_len = ETH_HWADDR_LEN;

/* set MAC hardware address */
memcpy(netif->hwaddr, netif->state, NETIF_MAX_HWADDR_LEN);

/* maximum transfer unit */
netif->mtu = 1500; /* TODO: define a config */

/* device capabilities */
/* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

/* ENET driver initialization.*/
if (kStatus_Success != operations.init_phy(0)) {
        LWIP_ASSERT("\r\nCannot initialize PHY.\r\n", 0);
    }

    volatile uint32_t count = 0;
    LinkStatus link_status;
    EnetSettings enet_settings;
    enet_settings.mac = netif->hwaddr;
    enet_settings.link_status.__status = 0;
    while ((count < ENET_ATONEGOTIATION_TIMEOUT)
            && (!enet_settings.link_status.linked)) {
        enet_settings.link_status = operations.get_link_status(0);
        count++;
    }

    EthernetMemIo ethernet_memio = { malloc, free };
    operations.init_ethernet(&ethernet_memio, &ethernet_io, &enet_settings);

#if LWIP_IPV6 && LWIP_IPV6_MLD
/*
 * For hardware/netifs that implement MAC filtering.
 * All-nodes link-local is handled by default, so we must let the hardware know
 * to allow multicast packets in.
 * Should set mld_mac_filter previously. */
if (netif->mld_mac_filter != NULL)
{
    ip6_addr_t ip6_allnodes_ll;
    ip6_addr_set_allnodes_linklocal(&ip6_allnodes_ll);
    netif->mld_mac_filter(netif, &ip6_allnodes_ll, NETIF_ADD_MAC_FILTER);
}
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */

return ERR_OK;
}
