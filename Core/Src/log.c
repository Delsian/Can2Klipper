/*
 * log.c
 *
 *  Created on: Jan 17, 2019
 *      Author: eug
 */

#include "string.h"
#include "stm32f0xx_hal.h"
#include "log.h"

UART_HandleTypeDef huart2;


void LogInit()
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	  //uint8_t a = 'a';
	  //HAL_UART_Transmit(&huart2, (uint8_t *)&a, 1, 100);
	lprint("hello");
}

void lprint(const uint8_t *msg)
{
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), 100);
}
