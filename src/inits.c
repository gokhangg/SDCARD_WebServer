/*
 * inits.c
 *
 *  Created on: Nov 19, 2018
 *      Author: gogo
 */
#include "inits.h"



/*! @brief SDMMC host detect card configuration */
static const sdmmchost_detect_card_t s_sdCardDetect = {
#ifndef BOARD_SD_DETECT_TYPE
		.cdType = kSDMMCHOST_DetectCardByGpioCD,
#else
		.cdType = BOARD_SD_DETECT_TYPE,
#endif
		.cdTimeOut_ms = (~0U), };

/*! @brief Card descriptor. */
sd_card_t g_sd;
sdhc_capability_t capability;

int initSDCARD(void) {
	sd_card_t *card = &g_sd;
	bool isReadOnly;
	card->host.base = SD_HOST_BASEADDR;
	card->host.sourceClock_Hz = SD_HOST_CLK_FREQ;
	card->usrParam.cd = &s_sdCardDetect;

	/* SD host init function */
	if (SD_HostInit(card) != kStatus_Success) {

		return -1;
	}

	/* power off card */
	SD_PowerOffCard(card->host.base, card->usrParam.pwr);

	if (SD_WaitCardDetectStatus(SD_HOST_BASEADDR, &s_sdCardDetect, true)
			== kStatus_Success) {

		/* reset host once card re-plug in */
		SD_HostReset(&(card->host));
		/* power on the card */
		SD_PowerOnCard(card->host.base, card->usrParam.pwr);
	} else {

		return -1;
	}
	/* Init card. */
	if (SD_CardInit(card)) {
		return -1;
	}
	/* Check if card is readonly. */
	isReadOnly = SD_CheckReadOnly(card);

	//SDHC_GetCapability(card->host.base, &capability);
}

void initPeripherals(void) {
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();
	SYSMPU_Enable(SYSMPU, false);
	initSDCARD();
}

