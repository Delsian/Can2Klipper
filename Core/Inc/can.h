/*
 * can.h
 *
 *  Created on: Jan 20, 2019
 *      Author: Eug
 */

#ifndef CORE_INC_CAN_H_
#define CORE_INC_CAN_H_


void CanInit(void);
void CanTransmit(uint8_t *pkt);

#endif /* CORE_INC_CAN_H_ */
