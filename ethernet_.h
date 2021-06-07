#pragma once
#include "stddef.h"
#include "stdint.h"



typedef struct {
	int (*get_rx_frame_size)(uint32_t*);
	int (*read_rx_frame)(uint8_t*, uint32_t);
	int (*send_tx_frame)(uint8_t*, uint32_t);
	void (*set_push_rx_frame_function)(int (*)(uint8_t*, uint32_t));
	void (*set_pull_tx_frame_function)(int (*)(uint8_t*, uint32_t));
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
	int (*init_phy)(const uint32_t);
	LinkStatus (*get_link_status)(const uint32_t);
	int (*init_ethernet)(const EthernetMemIo*, EthernetIo*, EnetSettings*);
}EnetOperations;

int GetEnetOperations(EnetOperations*);
int DeinitEthernet();

