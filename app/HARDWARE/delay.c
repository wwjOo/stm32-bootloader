#include "delay.h"


volatile uint32_t systick_cnt_ms = 0;


void delay_init(void)
{
	/* external clock: 72M/8=9M */
	SysTick->CTRL &= ~(1 << 2);
	
	
	/* 1ms */
	SysTick->LOAD = 9000;
	
	/* open exceptioin and count */
	SysTick->CTRL |= (1 << 1) | (1 << 0);
}								    


uint32_t getsystick_us(void)
{
	return (systick_cnt_ms*1000 + ((SysTick->LOAD-SysTick->VAL)*1000)/SysTick->LOAD);
}


void delay_us(uint32_t us)
{
	uint32_t now = getsystick_us();
	
	while(getsystick_us()-now < us);
}


void delay_ms(uint32_t ms)
{
	while(ms--)
	{
		delay_us(1000);
	}
}

