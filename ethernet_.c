#include "ethernet_.h"

#include "stdbool.h"

#include "fsl_enet.h"
#include "fsl_phy.h"

#define kMaxFrameSize ENET_FRAME_MAX_FRAMELEN
#define kEnetMemAlignment ENET_BUFF_ALIGNMENT
#define kRxBufferCount 5
#define kTxBufferCount 3
#define ENET_RING_NUM 1U
#define GET_ALIGNED(val, alignment) ( ((size_t)val + (size_t)alignment - 1) & ~(size_t)((size_t)alignment - 1) )

enet_handle_t enet_handle;

volatile enet_rx_bd_struct_t* allocated_rx_descriptors;
volatile enet_tx_bd_struct_t* allocated_tx_descriptors;
volatile enet_rx_bd_struct_t* rx_descriptors;
volatile enet_tx_bd_struct_t* tx_descriptors;

EthernetMemIo ethernet_mem_io;
uint8_t* rx_buff;
uint8_t* tx_buff;

EnetStatusE GetRxFrameSize(uint32_t* size) {
    status_t status = ENET_GetRxFrameSize(&enet_handle, size);
    switch (status) {
    case kStatus_ENET_RxFrameEmpty:
        return kEnetStatusRxFrameEmpty;
    case kStatus_ENET_RxFrameError:
        return kEnetStatusRxFrameError;
    case kStatus_Success:
        return kEnetStatusOk;
    };
    return kEnetStatusRxFrameEmpty;
}

EnetStatusE ReadRxFrame(uint8_t* data, uint32_t size) {
    return ENET_ReadFrame(ENET, &enet_handle, data, size) == kStatus_Success ?
            kEnetStatusOk : kStatus_ENET_RxFrameFail;
}

int SendTxFrame(uint8_t* data, uint32_t size) {
    return ENET_SendFrame(ENET, &enet_handle, data, size);
}

int InitEthernet(const EthernetMemIo* mem_io, EnetSettings* settings,
        EthernetIo* ethernet_io) {
    ethernet_io->get_rx_frame_size = GetRxFrameSize;
    ethernet_io->read_rx_frame = ReadRxFrame;
    ethernet_io->send_tx_frame = SendTxFrame;
    ethernet_io->set_pull_tx_frame_function = NULL;
    ethernet_io->set_push_rx_frame_function = NULL;
    ethernet_io->max_frame_size = ENET_FRAME_MAX_FRAMELEN;

    ethernet_mem_io = *mem_io;
    size_t buffer_size = GET_ALIGNED(kMaxFrameSize * kRxBufferCount,
            kEnetMemAlignment);
    rx_buff = ethernet_mem_io.malloc(buffer_size);

    buffer_size = GET_ALIGNED(kMaxFrameSize * kTxBufferCount,
            kEnetMemAlignment);
    tx_buff = ethernet_mem_io.malloc(buffer_size);

    buffer_size = GET_ALIGNED(sizeof(enet_rx_bd_struct_t) * kRxBufferCount,
            kEnetMemAlignment);
    allocated_rx_descriptors = ethernet_mem_io.malloc(buffer_size);
    rx_descriptors = (enet_rx_bd_struct_t*) GET_ALIGNED(
            allocated_rx_descriptors, kEnetMemAlignment);

    buffer_size = GET_ALIGNED(sizeof(enet_tx_bd_struct_t) * kTxBufferCount,
            kEnetMemAlignment);
    allocated_tx_descriptors = ethernet_mem_io.malloc(buffer_size);
    tx_descriptors = (enet_tx_bd_struct_t*) GET_ALIGNED(
            allocated_tx_descriptors, kEnetMemAlignment);

    enet_buffer_config_t buffCfg[ENET_RING_NUM];
    /* prepare the buffer configuration. */
    buffCfg[0].rxBdNumber = kRxBufferCount; /* Receive buffer descriptor number. */
    buffCfg[0].txBdNumber = kTxBufferCount; /* Transmit buffer descriptor number. */
    buffCfg[0].rxBuffSizeAlign = GET_ALIGNED(kMaxFrameSize * kRxBufferCount,
            kEnetMemAlignment); /* Aligned receive data buffer size. */
    buffCfg[0].txBuffSizeAlign = GET_ALIGNED(kMaxFrameSize * kRxBufferCount,
            kEnetMemAlignment); /* Aligned transmit data buffer size. */
    buffCfg[0].rxBdStartAddrAlign = rx_descriptors; /* Aligned receive buffer descriptor start address. */
    buffCfg[0].txBdStartAddrAlign = tx_descriptors; /* Aligned transmit buffer descriptor start address. */
    buffCfg[0].rxBufferAlign = (uint8_t *) GET_ALIGNED(rx_buff,
            kEnetMemAlignment); /* Receive data buffer start address. */
    buffCfg[0].txBufferAlign = (uint8_t *) GET_ALIGNED(tx_buff,
            kEnetMemAlignment); /* Transmit data buffer start address. */

    enet_config_t config;
    ENET_GetDefaultConfig(&config);
    config.ringNum = ENET_RING_NUM;
    config.miiSpeed = (enet_mii_speed_t) settings->link_status.speed;
    config.miiDuplex = (enet_mii_duplex_t) settings->link_status.duplex;

    uint32_t sysClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
    /* Initialize the ENET module.*/
    ENET_Init(ENET, &enet_handle, &config, &buffCfg[0], settings->mac,
            sysClock);

    ENET_ActiveRead(ENET);
    return 0;
}

EnetStatusE InitPhy(const uint32_t phy_address) {
    uint32_t sysClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
    return PHY_Init(ENET, phy_address, sysClock) == kStatus_Success ?
            kEnetStatusOk : kEnetStatusError;
}

LinkStatus GetLinkStatus(const uint32_t phy_address) {
    uint8_t link;
    LinkStatus status;
    status.__status = 0;
    PHY_GetLinkStatus(ENET, phy_address, (bool*) &link);
    if (link) {
        phy_speed_t speed;
        phy_duplex_t duplex;
        status.linked = 1;
        PHY_GetLinkSpeedDuplex(ENET, phy_address, &speed, &duplex);
        status.speed = speed;
        status.duplex = duplex;
    }
    return status;
}

int GetEnetOperations(EnetOperations* operations) {
    operations->init_phy = InitPhy;
    operations->get_link_status = GetLinkStatus;
    operations->init_ethernet = InitEthernet;
}
