#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"


#define led_state(x)	( (x == 0) ? GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET) : GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET) )


void led_init(void);
void led_state_ctrl(void);
void led_task(float T);


#endif


