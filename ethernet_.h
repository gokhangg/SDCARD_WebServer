#pragma once
#include "stddef.h"
#include "stdint.h"

//enum _enet_status
//{
//    kStatus_ENET_RxFrameError = MAKE_STATUS(kStatusGroup_ENET, 0U),   /*!< A frame received but data error happen. */
//    kStatus_ENET_RxFrameFail = MAKE_STATUS(kStatusGroup_ENET, 1U),    /*!< Failed to receive a frame. */
//    kStatus_ENET_RxFrameEmpty = MAKE_STATUS(kStatusGroup_ENET, 2U),   /*!< No frame arrive. */
//    kStatus_ENET_TxFrameOverLen = MAKE_STATUS(kStatusGroup_ENET, 3U), /*!< Tx frame over length. */
//    kStatus_ENET_TxFrameBusy = MAKE_STATUS(kStatusGroup_ENET, 4U),    /*!< Tx buffer descriptors are under process. */
//    kStatus_ENET_TxFrameFail = MAKE_STATUS(kStatusGroup_ENET, 5U)     /*!< Transmit frame fail. */
//#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
//    ,
//    kStatus_ENET_PtpTsRingFull = MAKE_STATUS(kStatusGroup_ENET, 6U), /*!< Timestamp ring full. */
//    kStatus_ENET_PtpTsRingEmpty = MAKE_STATUS(kStatusGroup_ENET, 7U) /*!< Timestamp ring empty. */
//#endif                                                               /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
//};

typedef enum  {
    kEnetStatusOk,
    kEnetStatusError,
    kEnetStatusRxFrameError,
    kEnetStatusRxFrameFail,
    kEnetStatusRxFrameEmpty,
    kEnetStatusTxFrameOverLen,
    kEnetStatusTxFrameBusy,
    kEnetStatusTxFrameFail
}EnetStatusE;



typedef struct {
    EnetStatusE (*get_rx_frame_size)(uint32_t*);
    EnetStatusE (*read_rx_frame)(uint8_t*, uint32_t);
	int (*send_tx_frame)(uint8_t*, uint32_t);
	void (*set_push_rx_frame_function)(int (*)(uint8_t*, uint32_t));
	void (*set_pull_tx_frame_function)(int (*)(uint8_t*, uint32_t));
	unsigned int max_frame_size;
}EthernetIo;

typedef struct {
	void *(*malloc)(size_t);
	void (*free)(void*);
}EthernetMemIo;

typedef union {
	uint8_t __status;
	struct {
		unsigned linked : 1;
		unsigned speed : 2;
		unsigned duplex : 1;
	};
}LinkStatus;

typedef struct {
	uint8_t* mac;
	LinkStatus link_status;
}EnetSettings;

typedef struct {
    EnetStatusE (*init_phy)(const uint32_t);
	LinkStatus (*get_link_status)(const uint32_t);
	int (*init_ethernet)(const EthernetMemIo*, EnetSettings*, EthernetIo*);
}EnetOperations;

int GetEnetOperations(EnetOperations*);
int DeinitEthernet();

