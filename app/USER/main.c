/*
 * STM32F103C8T6
 * FLASH : 64K
 * RAM   : 20K
 */
 
/*
 * ����Cortex�涨��0x00000000ȡջ��ֵ��Ȼ��ִ��0x00000004������
 * ��ST��������ʼ��ַ0x08000000ӳ�䵽��0x00000000���ʴ�0x00000000���0x08000000��ʼִ����һ�µ�
 * stm32ͨ������boot�ţ�����������ģʽѡ��������ģʽ�ı��ʾ��ǽ���Ӧ������ӳ��Ϊ0x00000000��ַ
 * ����������������������ַ��ʵ�ʻ��Ǵ�0x00000000��ʼִ�е�
 *
 * ����һ���ж�ʱ��cpu�ͻ��0x00000000+<������ƫ��ֵ>λ���ҵ��ж�������Ȼ���ٲ����ת����Ӧ���жϷ�����ȥִ��
 * �������ɶ��������ֻ��ͨ��VTORָ���������������λ�ü��ɣ�������ת��APP��������Ҫ�������ض�λ������λ�ã�
 * �Ա�ִ�е�ǰ����������������Ҷ�Ӧ�жϷ�����
 * �����ж�����������ã���https://www.eemaker.com/stm32-iap-vtor.html
 */

/*
 * �Զ�����.bin�ļ���������"option for target"userҳ���after build/rebuild�����룺
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






