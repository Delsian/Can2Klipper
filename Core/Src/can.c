/*
 * can.c
 *
 *  Created on: Jan 20, 2019
 *      Author: Eug
 */

#include <string.h>
#include "stm32f0xx_hal.h"
#include "can.h"

CAN_HandleTypeDef hcan;
void Error_Handler(void);

void CanInit(void)
{
	hcan.Instance = CAN;
	hcan.Init.Prescaler = 16;
	hcan.Init.Mode = CAN_MODE_NORMAL;
	hcan.Init.SJW = CAN_SJW_1TQ;
	hcan.Init.BS1 = CAN_BS1_1TQ;
	hcan.Init.BS2 = CAN_BS2_1TQ;
	hcan.Init.TTCM = DISABLE;
	hcan.Init.ABOM = DISABLE;
	hcan.Init.AWUM = DISABLE;
	hcan.Init.NART = DISABLE;
	hcan.Init.RFLM = DISABLE;
	hcan.Init.TXFP = DISABLE;
	if (HAL_CAN_Init(&hcan) != HAL_OK)
	{
		Error_Handler();
	}
}

void CanTransmit(uint16_t id, uint8_t len, uint8_t *pkt)
{
	hcan.pTxMsg->StdId = id;
	hcan.pTxMsg->DLC = len;
	memcpy(hcan.pTxMsg->Data, pkt, len);
}
