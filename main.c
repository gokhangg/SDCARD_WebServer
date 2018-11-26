/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Project: SDCARD Web Server
 * Author: ghngunay@gmail.com
*/

#include <stdio.h>
#include "inits.h"

#include "lwip/apps/httpd.h"
#include "lwip/timeouts.h"
#include "lwip/init.h"
#include "netif/ethernet.h"
#include "ethernetif.h"

#include "ff.h"


/*IP address*/
#define IP_ADD0 192
#define IP_ADD1 168
#define IP_ADD2 1
#define IP_ADD3 250

/*Netmask configuration*/
#define NET_MSK0 255
#define NET_MSK1 255
#define NET_MSK2 255
#define NET_MSK3 0

/*Gateway address configuration*/
#define GW_ADD0 192
#define GW_ADD1 168
#define GW_ADD2 1
#define GW_ADD3 249

/*MAC address*/
#define MAC_ADD {0x25, 0x25, 0x25, 0x25, 0x25, 0x25}

/*Filesystem object can be externed from other files*/
FATFS fs;

int main(void) {

	FRESULT res; /* API result code */
	struct netif fsl_netif0;
	ip4_addr_t fsl_netif0_ipaddr, fsl_netif0_netmask, fsl_netif0_gw;
	ethernetif_config_t fsl_enet_config0 = { .phyAddress = 0,
			.clockName = kCLOCK_CoreSysClk, .macAddress = MAC_ADD, };
	/*Initialize peripherals*/
	initPeripherals();
	/*SDCARD was initialized before so mount the volume*/
	res = f_mount(&fs, "2:", 1);
	/*Initialize systick timer*/
	time_init();
	/*preparation of ip address*/
	IP4_ADDR(&fsl_netif0_ipaddr, IP_ADD0, IP_ADD1, IP_ADD2,
			IP_ADD3);
	/*preparation of netmask address*/
	IP4_ADDR(&fsl_netif0_netmask, NET_MSK0, NET_MSK1,
			NET_MSK2, NET_MSK3);
	/*preparation of gateway address*/
	IP4_ADDR(&fsl_netif0_gw, GW_ADD0, GW_ADD1, GW_ADD2,
			GW_ADD3);

	/*Initialize lwip stack*/
	lwip_init();
	/*addition of active ethernet interface to the stack*/
	netif_add(&fsl_netif0, &fsl_netif0_ipaddr, &fsl_netif0_netmask,
			&fsl_netif0_gw, &fsl_enet_config0, ethernetif0_init,
			ethernet_input);
	/*Setting the created ethernet interface as default*/
	netif_set_default(&fsl_netif0);
	/*Seeting up the interface*/
	netif_set_up(&fsl_netif0);
	/*Initialization of http*/
	httpd_init();

	/*Printing the network details to uart port*/
	PRINTF("\r\n************************************************\r\n");
	PRINTF(" SDCARD Server example\r\n");
	PRINTF("************************************************\r\n");
	PRINTF(" IPv4 Address     : %u.%u.%u.%u\r\n",
			((u8_t *) &fsl_netif0_ipaddr)[0], ((u8_t *) &fsl_netif0_ipaddr)[1],
			((u8_t *) &fsl_netif0_ipaddr)[2], ((u8_t *) &fsl_netif0_ipaddr)[3]);
	PRINTF(" IPv4 Subnet mask : %u.%u.%u.%u\r\n",
			((u8_t *) &fsl_netif0_netmask)[0],
			((u8_t *) &fsl_netif0_netmask)[1],
			((u8_t *) &fsl_netif0_netmask)[2],
			((u8_t *) &fsl_netif0_netmask)[3]);
	PRINTF(" IPv4 Gateway     : %u.%u.%u.%u\r\n", ((u8_t *) &fsl_netif0_gw)[0],
			((u8_t *) &fsl_netif0_gw)[1], ((u8_t *) &fsl_netif0_gw)[2],
			((u8_t *) &fsl_netif0_gw)[3]);
	PRINTF("************************************************\r\n");

	/*wait for connection and request*/
	while (1) {
		/* Poll the driver, get any outstanding frames */
		ethernetif_input(&fsl_netif0);

		sys_check_timeouts(); /* Handle all system timeouts for all core protocols */
	}
}

void SysTick_Handler(void) {
	time_isr();
}

