#ifndef __FLASH_H
#define __FLASH_H
#include "stm32f10x.h"



/* medium-density devices FLASH */
/*   0x08000000 - 0x0801FFFF    */
#define FLASH_BASE_ADDR	0x08000000
#define FLASH_PAGE_NUM	128

#define PAGEX_ADDR(X)	(FLASH_BASE_ADDR + 1024 * ((X > FLASH_PAGE_NUM - 1) ? (FLASH_PAGE_NUM - 1) : X))



uint8_t FLASH_Write_HalfWord(uint32_t addr, uint16_t val);
uint8_t FLASH_Write_Word(uint32_t addr, uint32_t val);
uint8_t FLASH_Erase_Page(uint32_t Page_addr);


#endif


