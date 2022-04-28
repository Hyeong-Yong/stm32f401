/*
 * hw.c
 *
 *  Created on: Apr 28, 2022
 *      Author: HYJH
 */

#include "hw.h"

void hwInit()
{
  bspInit();
  ledInit();
  usbInit();
}

