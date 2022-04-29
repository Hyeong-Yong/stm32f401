/*
 * button.h
 *
 *  Created on: 2022. 4. 28.
 *      Author: HYJH
 */

#ifndef COMMON_INCLUDE_BUTTON_H_
#define COMMON_INCLUDE_BUTTON_H_

#include "hw_def.h"
#ifdef _USE_HW_BUTTON

#define BUTTON_MAX_CH	HW_BUTTON_MAX_CH

bool buttonInit();
bool buttonGetPressed(uint8_t ch);

#endif

#endif /* COMMON_INCLUDE_BUTTON_H_ */
