
#include "ethernet_.h"

#include "lwip/init.h"
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "netif/etharp.h"
#include "lwip/apps/httpd.h"
#include "lwip/timeouts.h"
#include <stdlib.h>
#include "string.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

EnetOperations operations;
EthernetIo ethernet_io;


#define ENET_OK             (0U)
#define ENET_ERROR          (0xFFU)
#define ENET_TIMEOUT        (0xFFFU)


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
    static unsigned char ucBuffer[1600];
    pucBuffer = ucBuffer;
    if (pucBuffer == NULL) {
        return ERR_BUF;
    }

    /* Initiate transfer. */

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

    if (p->len == p->tot_len) {

        /* No pbuf chain, don't have to copy -> faster. */
        pucBuffer = (unsigned char *) p->payload;
    } else {
        /* pbuf chain, copy into contiguous ucBuffer. */
        if (p->tot_len >= ethernet_io.max_frame_size) {
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
        if (ethernet_io.send_tx_frame(pucBuffer, p->tot_len)
                != kEnetStatusTxFrameBusy) {
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
    EnetStatusE status;
    /* Obtain the size of the packet and put it into the "len"
     variable. */
    status = ethernet_io.get_rx_frame_size(&len);
    if (kEnetStatusRxFrameEmpty != status) {
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
                    uint8_t data_tmp[1600];
                    uint32_t data_tmp_len = 0;

                    ethernet_io.read_rx_frame(data_tmp, p->tot_len);

                    /* We iterate over the pbuf chain until we have read the entire
                     * packet into the pbuf. */
                    for (q = p;
                            (q != NULL)
                                    && ((data_tmp_len + q->len)
                                            <= sizeof(data_tmp)); q = q->next) {
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
            if (status == kEnetStatusRxFrameError) {
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
    netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP
            | NETIF_FLAG_LINK_UP;

    /* ENET driver initialization.*/
    if (kEnetStatusOk != operations.init_phy(0)) {
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
    operations.init_ethernet(&ethernet_memio, &enet_settings, &ethernet_io);

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

/*IP address*/
#define IP_ADD0 192
#define IP_ADD1 168
#define IP_ADD2 178
#define IP_ADD3 250

/*Netmask configuration*/
#define NET_MSK0 255
#define NET_MSK1 255
#define NET_MSK2 255
#define NET_MSK3 0

/*Gateway address configuration*/
#define GW_ADD0 192
#define GW_ADD1 168
#define GW_ADD2 178
#define GW_ADD3 249

/*MAC address*/
unsigned char MAC_ADD[6] = { 0x25, 0x25, 0x25, 0x25, 0x25, 0x25 };

static struct netif netif0;

void InitLwip() {

    ip4_addr_t fsl_netif0_ipaddr, fsl_netif0_netmask, fsl_netif0_gw;

    /*preparation of ip address*/
    IP4_ADDR(&fsl_netif0_ipaddr, IP_ADD0, IP_ADD1, IP_ADD2, IP_ADD3);
    /*preparation of netmask address*/
    IP4_ADDR(&fsl_netif0_netmask, NET_MSK0, NET_MSK1, NET_MSK2, NET_MSK3);
    /*preparation of gateway address*/
    IP4_ADDR(&fsl_netif0_gw, GW_ADD0, GW_ADD1, GW_ADD2, GW_ADD3);

    /*Initialize lwip stack*/
    lwip_init();
    /*addition of active ethernet interface to the stack*/
    netif_add(&netif0, &fsl_netif0_ipaddr, &fsl_netif0_netmask, &fsl_netif0_gw,
            MAC_ADD, ethernetif0_init, ethernet_input);
    /*Setting the created ethernet interface as default*/
    netif_set_default(&netif0);
    /*Seeting up the interface*/
    netif_set_up(&netif0);
    /*Initialization of http*/
    httpd_init();
}

void LwipLoop() {
    ethernetif_input(&netif0);

    sys_check_timeouts(); /* Handle all system timeouts for all core protocols */
}

