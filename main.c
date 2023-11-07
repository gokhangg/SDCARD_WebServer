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


#include "inits.h"

#include "ff.h"

#include "ethernetif.h"



/*Filesystem object can be externed from other files*/
FATFS fs;
uint32_t var;

#include <stdio.h>
#include <stdlib.h>

const EnetOperations* InitEnet();

int main(void) {

    FRESULT res; /* API result code */
    /*Initialize peripherals*/
    initPeripherals();
    /*SDCARD was initialized before so mount the volume*/
    res = f_mount(&fs, "2:", 1);
    /*Initialize systick timer*/
    time_init();
    const EnetOperations* operations = InitEnet();
    InitLwip(&operations->enet_io);

    while (1) {
        /* Poll the driver, get any outstanding frames */
        //LwipLoop();
    }
}

#define ENET_AUTONEGOTIATION_TIMEOUT     (0xFFFU)

const EnetOperations* InitEnet() {
    /*MAC address*/
    const EnetOperations* operations = GetEnetOperations();
    /* ENET driver initialization.*/
    if (kEnetStatusOk != operations->init_phy(0)) {
    }
    volatile uint32_t count = 0;
    LinkStatus link_status;
    EnetSettings enet_settings;
    enet_settings.mac = operations->enet_io.mac;
    enet_settings.link_status.__status = 0;
    while ((count < ENET_AUTONEGOTIATION_TIMEOUT)
            && (!enet_settings.link_status.linked)) {
        enet_settings.link_status = operations->get_link_status(0);
        count++;
    }

    EthernetMemIo ethernet_memio = { malloc, free };
    operations->init_ethernet(&ethernet_memio, &enet_settings);
    return operations;
}
