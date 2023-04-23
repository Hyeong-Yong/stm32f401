/*
 * flash.c
 *
 *  Created on: 2022. 2. 10.
 *      Author: HYJH
 */

#ifndef SRC_HW_DRIVER_FLASH_C_
#define SRC_HW_DRIVER_FLASH_C_


#include "flash.h"
#include "cli.h"

#ifdef _USE_HW_FLASH

#define FLASH_SECTOR_MAX    6  //stm32f1 => flash memory size 64kByte
			       //stm32f401 => flash memor size 16K[0~3] + 64K[4]+ 128K[1]

typedef struct
{
  uint32_t addr;
  uint32_t length;
} flash_tbl_t;

static flash_tbl_t flash_tbl[FLASH_SECTOR_MAX]=
    {
	{0x08000000,  16*1024},
	{0x08004000,  16*1024},
	{0x08008000,  16*1024},
	{0x0800C000,  16*1024},
	{0x08010000,  64*1024},
	{0x08020000, 128*1024},
    };

static bool flashInSector(uint16_t sector_num, uint32_t addr, uint32_t length);

#ifdef _USE_HW_CLI
static void cliFlash(cli_args_t* args);
#endif

bool flashInit()
{

#ifdef _USE_HW_CLI
cliAdd("flash", cliFlash);
#endif

    return true;
}

bool flashInSector(uint16_t sector_num, uint32_t addr, uint32_t length)
{
  bool ret= false;

  uint32_t sector_start;
  uint32_t sector_end;
  uint32_t flash_start;
  uint32_t flash_end;

  sector_start  = flash_tbl[sector_num].addr;
  sector_end    = flash_tbl[sector_num].addr + flash_tbl[sector_num].length - 1;
  flash_start   = addr;
  flash_end     = addr + length - 1;

  if (sector_start >= flash_start && sector_start <= flash_end)
    {
      ret = true; //1
    }
  if (sector_end >= flash_start && sector_end <= flash_end)
    {
      ret = true;   //2  // 1,2 설명-> 지워야할 flash 메모리가 sector 보다 클 떄, sector 는 flash 양끝 안에 있어야한다.
    }
  if (flash_start >= sector_start && flash_start <= sector_end)
    {
      ret = true;
    }
  if (flash_end >= sector_start && flash_end <= sector_end)
    {
      ret = true;
    }
  return ret;
}

bool flashErase(uint32_t addr, uint32_t length) //flash를 지울때는 sector 단위로 지울수 있으며,
{
bool ret=false;

HAL_StatusTypeDef status;
FLASH_EraseInitTypeDef init;
uint32_t page_error;

int16_t start_sector_num = -1;
uint32_t sector_count = 0;

for (int i=0; i<FLASH_SECTOR_MAX; i++)
  {
    if (flashInSector(i, addr, length)==true)
      {
        if (start_sector_num < 0)
          {
            start_sector_num = i;
          }
        sector_count++;
      }
  }

if (sector_count > 0)
  {
    HAL_FLASH_Unlock();
init.TypeErase    = FLASH_TYPEERASE_SECTORS;
init.Banks        = FLASH_BANK_1;
init.Sector 	  = start_sector_num;
init.NbSectors    = sector_count;
init.VoltageRange = FLASH_VOLTAGE_RANGE_3;

status = HAL_FLASHEx_Erase(&init, &page_error);
    if (status==HAL_OK)
      {
        ret = true;
      }
    HAL_FLASH_Lock();
  }

return ret;
}

bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length) // 쓰고 읽을때는 바이트나 워드단위로 사용할수 있다
{
bool ret = true;

HAL_StatusTypeDef status;

HAL_FLASH_Unlock();

for (int i = 0 ; i<length ; i++)
  {
    uint8_t data;

    data  = p_data[i];
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, addr+i, (uint64_t)data);
    if (status!=HAL_OK)
      {
        ret = false;
        break;
      }
}
HAL_FLASH_Lock();

return ret;
}

bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length)
{
  bool ret=true;

  uint8_t *p_byte = (uint8_t *)addr;

  for (int i=0; i<length; i++)
    {
      p_data[i]=p_byte[i];
    }

return ret;
}

#ifdef _USE_HW_CLI
void cliFlash(cli_args_t* args)
{
  bool ret = false;

  if(args->argc==1 && args->isStr(0, "info") == true)
  {
    for (int i =0 ; i<FLASH_SECTOR_MAX;i++)
    {
      cliPrintf("0x%X : %dKB\n", flash_tbl[i].addr, flash_tbl[i].length/1024);
    }
    ret= true;
  }

  if(args->argc== 3 && args->isStr(0, "read") == true)
  {
    uint32_t addr;
    uint32_t length;

    addr = (uint32_t)args->getData(1);
    length = (uint32_t)args->getData(2);

    for (int i=0; i<length; i++)
    {
      cliPrintf("0x%X : 0x%X\n", addr+i, *((uint8_t*)(addr+i)));
    }

    ret =true;
  }

  if(args->argc == 3 && args->isStr(0, "erase")== true)
  {
    uint32_t addr;
    uint32_t length;

    addr = (uint32_t)args->getData(1);
    length = (uint32_t)args->getData(2);

    if (flashErase(addr, length) == true)
    {
      cliPrintf("Erase success.\n");
    }
    else
    {
      cliPrintf("Erase fail.\n");
    }
    ret=true;
  }

  if (args->argc==3 && args->isStr(0, "write")==true)
  {
    uint32_t addr;
    uint32_t data;

    addr = (uint32_t)args->getData(1);
    data = (uint32_t)args->getData(2);

    if(flashWrite(addr, (uint8_t *)&data, 4)==true)
    {
      cliPrintf("Write success.\n");
    }
    else
    {
      cliPrintf("Write fail.\n");
    }

    ret = true;
  }

  if (ret !=true)
  {
    cliPrintf("flash info\n");
    cliPrintf("flash read addr length\n");
    cliPrintf("flash erase addr length\n");
    cliPrintf("flash write addr length\n");
  }
}

#endif

#endif

#endif /* SRC_HW_DRIVER_FLASH_C_ */
