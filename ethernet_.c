#include "ethernet_.h"

#define NETIF_MAX_HWADDR_LEN 6
#include "stdbool.h"

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "netif/etharp.h"
#include "netif/ppp/pppoe.h"
#include "lwip/igmp.h"
#include "lwip/mld6.h"

#if USE_RTOS && defined(FSL_RTOS_FREE_RTOS)
#include "FreeRTOS.h"
#include "event_groups.h"
#endif

#include "ethernetif.h"

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

int GetRxFrameSize(uint32_t* size) {
	return ENET_GetRxFrameSize(&enet_handle, size);
}

int ReadRxFrame(uint8_t* data, uint32_t size) {
	return ENET_ReadFrame(ENET, &enet_handle, data, size);;
}

int SendTxFrame(uint8_t* data, uint32_t size) {
	return ENET_SendFrame(ENET, &enet_handle, data, size);
}


int InitEthernet(const EthernetMemIo* mem_io, EthernetIo* ethernet_io, EnetSettings* settings) {
	ethernet_io->get_rx_frame_size = GetRxFrameSize;
	ethernet_io->read_rx_frame = ReadRxFrame;
	ethernet_io->send_tx_frame = SendTxFrame;
	ethernet_io->set_pull_tx_frame_function = NULL;
	ethernet_io->set_push_rx_frame_function = NULL;

	ethernet_mem_io = *mem_io;
	size_t buffer_size = GET_ALIGNED(kMaxFrameSize * kRxBufferCount, kEnetMemAlignment);
	rx_buff = ethernet_mem_io.malloc(buffer_size);

	buffer_size = GET_ALIGNED(kMaxFrameSize * kTxBufferCount, kEnetMemAlignment);
	tx_buff = ethernet_mem_io.malloc(buffer_size);

	buffer_size = GET_ALIGNED(sizeof(enet_rx_bd_struct_t) * kRxBufferCount, kEnetMemAlignment);
	allocated_rx_descriptors = ethernet_mem_io.malloc(buffer_size);
	rx_descriptors = (enet_rx_bd_struct_t*)GET_ALIGNED(allocated_rx_descriptors, kEnetMemAlignment);

	buffer_size = GET_ALIGNED(sizeof(enet_tx_bd_struct_t) * kTxBufferCount, kEnetMemAlignment);
	allocated_tx_descriptors = ethernet_mem_io.malloc(buffer_size);
	tx_descriptors = (enet_tx_bd_struct_t*)GET_ALIGNED(allocated_tx_descriptors, kEnetMemAlignment);

	enet_buffer_config_t buffCfg[ENET_RING_NUM];
	/* prepare the buffer configuration. */
	buffCfg[0].rxBdNumber = kRxBufferCount;                      /* Receive buffer descriptor number. */
	buffCfg[0].txBdNumber = kTxBufferCount;                      /* Transmit buffer descriptor number. */
	buffCfg[0].rxBuffSizeAlign = GET_ALIGNED(kMaxFrameSize * kRxBufferCount, kEnetMemAlignment);           /* Aligned receive data buffer size. */
	buffCfg[0].txBuffSizeAlign = GET_ALIGNED(kMaxFrameSize * kRxBufferCount, kEnetMemAlignment);           /* Aligned transmit data buffer size. */
	buffCfg[0].rxBdStartAddrAlign = rx_descriptors; /* Aligned receive buffer descriptor start address. */
	buffCfg[0].txBdStartAddrAlign = tx_descriptors; /* Aligned transmit buffer descriptor start address. */
	buffCfg[0].rxBufferAlign = (uint8_t *)GET_ALIGNED(rx_buff, kEnetMemAlignment); /* Receive data buffer start address. */
	buffCfg[0].txBufferAlign = (uint8_t *)GET_ALIGNED(tx_buff, kEnetMemAlignment); /* Transmit data buffer start address. */


	enet_config_t config;
	ENET_GetDefaultConfig(&config);
	config.ringNum = ENET_RING_NUM;
	config.miiSpeed = (enet_mii_speed_t)settings->link_status.speed;
	config.miiDuplex = (enet_mii_duplex_t)settings->link_status.duplex;


	#if USE_RTOS && defined(FSL_RTOS_FREE_RTOS)
	    uint32_t instance;
	    static ENET_Type *const enetBases[] = ENET_BASE_PTRS;
	    static const IRQn_Type enetTxIrqId[] = ENET_Transmit_IRQS;
	    /*! @brief Pointers to enet receive IRQ number for each instance. */
	    static const IRQn_Type enetRxIrqId[] = ENET_Receive_IRQS;
	#if defined(ENET_ENHANCEDBUFFERDESCRIPTOR_MODE) && ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
	    /*! @brief Pointers to enet timestamp IRQ number for each instance. */
	    static const IRQn_Type enetTsIrqId[] = ENET_1588_Timer_IRQS;
	#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

	    /* Create the Event for transmit busy release trigger. */
	    ethernetif->enetTransmitAccessEvent = xEventGroupCreate();
	    ethernetif->txFlag = 0x1;

	    config.interrupt |= kENET_RxFrameInterrupt | kENET_TxFrameInterrupt | kENET_TxBufferInterrupt;

	    for (instance = 0; instance < ARRAY_SIZE(enetBases); instance++)
	    {
	        if (enetBases[instance] == ethernetif->base)
	        {
	#ifdef __CA7_REV
	            GIC_SetPriority(enetRxIrqId[instance], ENET_PRIORITY);
	            GIC_SetPriority(enetTxIrqId[instance], ENET_PRIORITY);
	#if defined(ENET_ENHANCEDBUFFERDESCRIPTOR_MODE) && ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
	            GIC_SetPriority(enetTsIrqId[instance], ENET_1588_PRIORITY);
	#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
	#else
	            NVIC_SetPriority(enetRxIrqId[instance], ENET_PRIORITY);
	            NVIC_SetPriority(enetTxIrqId[instance], ENET_PRIORITY);
	#if defined(ENET_ENHANCEDBUFFERDESCRIPTOR_MODE) && ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
	            NVIC_SetPriority(enetTsIrqId[instance], ENET_1588_PRIORITY);
	#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
	#endif /* __CA7_REV */
	            break;
	        }
	    }

	    LWIP_ASSERT("Input Ethernet base error!", (instance != ARRAY_SIZE(enetBases)));
	#endif /* USE_RTOS */

	    uint32_t sysClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
	    /* Initialize the ENET module.*/
	    ENET_Init(ENET, &enet_handle, &config, &buffCfg[0], settings->mac, sysClock);

	#if USE_RTOS && defined(FSL_RTOS_FREE_RTOS)
	    ENET_SetCallback(&ethernetif->handle, ethernet_callback, netif);
	#endif

	    ENET_ActiveRead(ENET);
	   return 0;
}

int InitPhy(const uint32_t phy_address) {
	uint32_t sysClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
	return PHY_Init(ENET, phy_address, sysClock);
}

LinkStatus GetLinkStatus(const uint32_t phy_address) {
	uint8_t link;
	LinkStatus status;
	status.__status = 0;
	PHY_GetLinkStatus(ENET, phy_address, (bool*)&link);
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



err_t ethernetif1_init(struct netif *netif) {


	//ethernetif->RxBuffDescrip = rx_descriptors;
	//ethernetif->TxBuffDescrip = tx_descriptors;
	//ethernetif->RxDataBuff = (uint8_t*)GET_ALIGNED(rx_buff, kEnetMemAlignment);
	//ethernetif->TxDataBuff = (uint8_t*)GET_ALIGNED(tx_buff, kEnetMemAlignment);

	return 0;// ethernetif_init(netif, &ethernetif_0, 0U, (ethernetif_config_t *)netif->state);
}
