#ifndef __DELAY_H
#define __DELAY_H 
#include "stm32f10x.h"


void delay_init(void);
uint32_t getsystick_us(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);


extern volatile uint32_t systick_cnt_ms;


#endif





























