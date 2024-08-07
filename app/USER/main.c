/*
 * STM32F103C8T6
 * FLASH : 64K
 * RAM   : 20K
 */
 
/*
 * 由于Cortex规定从0x00000000取栈顶值，然后执行0x00000004的内容
 * 因ST将闪存起始地址0x08000000映射到了0x00000000，故从0x00000000与从0x08000000开始执行是一致的
 * stm32通过配置boot脚，有三种启动模式选择，这三种模式的本质就是将对应区域重映射为0x00000000地址
 * 将代码放置在闪存的其他地址，实际还是从0x00000000开始执行的
 *
 * 当来一个中断时，cpu就会从0x00000000+<向量表偏移值>位置找到中断向量表，然后再查表跳转到对应的中断服务函数去执行
 * 可以容纳多个向量表，只需通过VTOR指定你所需的向量表位置即可，故在跳转到APP程序后的首要任务是重定位向量表位置，
 * 以便执行当前程序的向量表来查找对应中断服务函数
 * 关于中断向量表的重置，看https://www.eemaker.com/stm32-iap-vtor.html
 */

/*
 * 自动生成.bin文件方法：在"option for target"user页面的after build/rebuild中填入：
 * fromelf.exe --bin -o "$L@L.bin" "#L"
 */

#include "delay.h"
#include "led.h"
#include "oled.h"
#include "lcd.h"
#include "AMG8833.h"


extern const unsigned char gImage_1[3200];

u16 k,j;
int main(void)
{
	/*
	 * @param Offset: Vector Table base offset field. This value must be a multiple of 0x200.
	 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x3000);
	
	delay_init();
	led_init();
	lcd_init();
	oled_init();
	
	AMG88xx_Init();
	
			
	k = getsystick_us();
	lcd_test(WHITE);
	oled_test();
	k = getsystick_us() - k;
	
	oled_show_num(20,20,16,k,1);
	OLED_Refresh();
	delay_ms(5000);
	
	while(1)
	{
		AMG88xx_read();
		for(k = 0; k < 8; k++)
		{
			for(j = 0; j < 8; j++)
			{
				lcd_DMAFill(j*10,k*10,10,10,&AMG_Buf[8*k + j],DMA_MemoryInc_Disable);
				delay_us(500);
			}
		}
	}
}






