/*
 * ap.c
 *
 *  Created on: Apr 28, 2022
 *      Author: HYJH
 */

#include "ap.h"
#include "def.h"
void apInit()
{
  cliOpen(_DEF_UART1, 57600);
  spiBegin(_DEF_SPI1);

}

void apMain()
{
  uint32_t pre_time=0;
  while (1)
  {
    if (millis()-pre_time >= 2000)
    {
      pre_time = millis();
      //ledToggle(_DEF_LED1);
    }

    cliMain();
  }
}
