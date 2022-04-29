/*
 * hw_def.h
 *
 *  Created on: Apr 28, 2022
 *      Author: HYJH
 */

#ifndef HW_HW_DEF_H_
#define HW_HW_DEF_H_

#include "def.h"
#include "bsp.h"

#define _USB_HW_USB
//#define _USE_HW_RTC
//#define _USB_HW_RESET
#define _USE_HW_CDC
#define _USE_HW_GPIO
#define      HW_GPIO_MAX_CH      3
#define _USE_HW_BUTTON
#define	     HW_BUTTON_MAX_CH	 1

#define _USE_HW_SPI
#define      HW_SPI_MAX_CH	 1

#define _USE_HW_DAC

#define _USE_HW_FLASH

//#define _USE_HW_MOTOR
//#define      HW_MOTOR_PKT_BUF_MAX   10

#define _USE_HW_LED
#define      HW_LED_MAX_CH       1

#define _USE_HW_UART
#define      HW_UART_MAX_CH      1

#define _USE_HW_CLI
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_CMD_LIST_MAX    16
#define      HW_CLI_LINE_HIS_MAX    4
#define      HW_CLI_LINE_BUF_MAX    64

#define _USE_HW_LCD
#define _USE_HW_ST7735
#define      HW_LCD_WIDTH	160
#define      HW_LCD_HEIGHT	 80



#endif /* HW_HW_DEF_H_ */
