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

}

void apMain()
{
  uint32_t pre_time=0;
  while (1)
  {
    if (millis()-pre_time >= 2000)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }


  }
}
