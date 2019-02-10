/*
 * can.c
 *
 *  Created on: Jan 20, 2019
 *      Author: Eug
 */

#include <string.h>
#include "stm32f0xx_hal.h"
#include "can.h"
#include "log.h"

CAN_HandleTypeDef hcan;
static CanTxMsgTypeDef    TxMessage;
static CanRxMsgTypeDef    RxMessage;
CAN_FilterConfTypeDef sFilterConfig;
void Error_Handler(void);

void CanInit(void)
{
	hcan.Instance = CAN;
	hcan.Init.Prescaler = 6;
	hcan.Init.Mode = CAN_MODE_NORMAL;
	hcan.Init.SJW = CAN_SJW_1TQ;
	hcan.Init.BS1 = CAN_BS1_5TQ;
	hcan.Init.BS2 = CAN_BS2_2TQ;
	hcan.Init.TTCM = DISABLE;
	hcan.Init.ABOM = DISABLE;
	hcan.Init.AWUM = DISABLE;
	hcan.Init.NART = ENABLE;
	hcan.Init.RFLM = DISABLE;
	hcan.Init.TXFP = DISABLE;
	if (HAL_CAN_Init(&hcan) != HAL_OK)
	{
		Error_Handler();
	}
	hcan.pTxMsg = &TxMessage;
	hcan.pRxMsg = &RxMessage;

	/*##-2- Configure the CAN Filter ###########################################*/
	 sFilterConfig.FilterNumber = 0;
	 sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	 sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	 sFilterConfig.FilterIdHigh = 0;
	 sFilterConfig.FilterIdLow = 0;
	 sFilterConfig.FilterMaskIdHigh = 0x0000;
	 sFilterConfig.FilterMaskIdLow = 0x0000;
	 sFilterConfig.FilterFIFOAssignment = CAN_FIFO0;
	 sFilterConfig.FilterActivation = ENABLE;
	 //sFilterConfig.BankNumber = 14;

	 if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
		 /* Filter configuration Error */
		 Error_Handler();

	 /*##-3- Configure Transmission process #####################################*/
	 hcan.pTxMsg->StdId = 0x1;
	 hcan.pTxMsg->ExtId = 0;
	 hcan.pTxMsg->RTR = CAN_RTR_DATA;
	 hcan.pTxMsg->IDE = CAN_ID_STD;
	 hcan.pTxMsg->DLC = 8;

	 //HAL_CAN_Start(&hcan);
	 HAL_CAN_Receive_IT(&hcan, CAN_FIFO0);
}

void CanTransmit(uint8_t *pkt)
{
	memcpy(hcan.pTxMsg->Data, pkt, 8);
	HAL_CAN_Transmit(&hcan, 1000);
}

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* h) {
	memcpy(hcan.pTxMsg->Data,h->pRxMsg->Data,h->pRxMsg->DLC);
	HAL_CAN_Transmit(&hcan, 1000);
	lprint(itoa(h->pRxMsg->StdId));
}
