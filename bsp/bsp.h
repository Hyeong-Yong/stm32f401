/*
 * bsp.h
 *
 *  Created on: Apr 28, 2022
 *      Author: HYJH
 */

#ifndef BSP_BSP_H_
#define BSP_BSP_H_

#include "def.h"
#include "stm32f4xx_hal.h"


void bspInit();
void Error_Handler(void);
uint32_t millis(void);
int __io_putchar(int ch);
void delay(uint32_t ms);

#endif /* BSP_BSP_H_ */
