/*
 * def.h
 *
 *  Created on: Apr 28, 2022
 *      Author: HYJH
 */

#ifndef COMMON_DEF_H_
#define COMMON_DEF_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define _DEF_LED1    0
#define _DEF_LED2    1
#define _DEF_LED3    2
#define _DEF_LED4    3

#define _DEF_UART1   0  // USB_CDC communication
#define _DEF_UART2   1  // UART
#define _DEF_UART3   2
#define _DEF_UART4   3

#define _DEF_MOTOR1 0
#define _DEF_MOTOR2 1

#define _DEF_BUTTON1 0
#define _DEF_BUTTON2 1
#define _DEF_BUTTON3 2
#define _DEF_BUTTON4 3

#define _DEF_INPUT		0
#define _DEF_INPUT_PULLUP	1
#define _DEF_INPUT_PULLDOWN	2
#define _DEF_OUTPUT		3
#define _DEF_OUTPUT_PULLUP	4
#define _DEF_OUTPUT_PULLDOWN	5

#define _DEF_SPI1 		0  //DAC_MSP4822
#define _DEF_SPI2 		1  //LCD_ST7735

#define _DEF_DAC_CS		0  //GPIO DAC_CS
#define _DEF_DAC_LDAC		1  //GPIO DAC_LDAC

#define _DEF_LOW		0
#define _DEF_HIGH		1



#endif /* COMMON_DEF_H_ */
