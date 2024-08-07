#include "led.h"


void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	/* on */
	led_state(1);
}


#define BRIGHTNESS_MAX	20
#define BRIGHTNESS_MIN	0


/* ctrl on off */
#define LED_NUM  1
uint8_t brightness[LED_NUM]={0};

void led_state_ctrl(void)
{
	uint8_t i;
	static uint8_t cnt[LED_NUM];
	
	for(i=0; i<LED_NUM; i++)
	{
		if(cnt[i] < brightness[i])
		{
			switch(i)
			{
				case 0 : led_state(1); break;
			}
		}
		else
		{
			switch(i)
			{
				case 0 : led_state(0); break;
			}
		}
		
		if(cnt[i]++ > BRIGHTNESS_MAX)
		{
			cnt[i] = 0;
		}
	}
}


/* breath ctrl */
uint8_t led_breath(uint8_t led_num)
{
	uint8_t breath_finished=0;
	static uint8_t step[LED_NUM];
	
	switch(step[led_num])
	{
		case 0:
		{
			brightness[led_num] += 1;
			
			if(brightness[led_num] >= BRIGHTNESS_MAX)
			{
				step[led_num] = 1;
			}
			
			break;
		}
		
		case 1:
		{
			brightness[led_num] -= 1;
			
			if(brightness[led_num] <= BRIGHTNESS_MIN)
			{
				step[led_num] = 0;
				breath_finished = 1;
			}
			
			break;
		}
		
		default :
		{
			step[led_num] = 0;
			break;
		}
	}
	
	return breath_finished;
}


/* flash ctrl */
float time_cnt[LED_NUM]={0};
uint8_t flash_time_cnt[LED_NUM]={0};
/** 
	@param \\ 灯序号  亮度  闪烁次数  亮的时间  灭的时间  间断时间  函数执行周期ms \\ 
**/
uint8_t led_flash(uint8_t led_num,uint8_t led_brightness,uint8_t led_flash_time,float led_on_time,float led_off_time,float led_gap_time,float T)
{
	uint8_t flash_finished=0;

	if(led_brightness > BRIGHTNESS_MAX)
	{
		led_brightness = BRIGHTNESS_MAX;
	}
	
	if(flash_time_cnt[led_num] < led_flash_time) /* flashing */
	{
		if(time_cnt[led_num] < led_on_time)
		{
			brightness[led_num] = led_brightness; /* ON */
		}
		else if(time_cnt[led_num] < (led_on_time+led_off_time))
		{
			brightness[led_num] = 0; /* OFF */
		}
		else
		{
			time_cnt[led_num] = 0;
			flash_time_cnt[led_num]++;
		}
	}
	
	else /* flash gap */
	{
		if(time_cnt[led_num] < led_gap_time)
		{
			brightness[led_num] = 0;
		}
		else
		{
			time_cnt[led_num] = 0;
			flash_time_cnt[led_num] = 0;
			
			flash_finished = 1;
		}
	}
	
	time_cnt[led_num] += T;
	
	return flash_finished;
}



/* reset */
void led_reset(void)
{
	uint8_t i;
	
	for(i=0; i<LED_NUM; i++)
	{
		time_cnt[i] = 0;
		brightness[i] = 0;
		flash_time_cnt[i] = 0;
	}
}


/* mode change check */
uint8_t led_lightmode=0;
uint8_t led_lightmode_old=0;
void led_lightmode_check(void)
{
	if(led_lightmode != led_lightmode_old)
	{
		led_lightmode_old = led_lightmode;
		led_reset();
	}
}


/* task */
void led_task(float T)
{
	led_lightmode_check();
	
	switch(led_lightmode)
	{
		case 0: 
			led_breath(0);
			break;
		default:
			led_breath(0);
			break;
	}
}



/* end of led.c */



