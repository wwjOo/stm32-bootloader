#ifndef __LCD_H
#define __LCD_H
#include "stm32f10x.h"


#define LCD_RES_L()  	GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define LCD_RES_H()  	GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define LCD_DC_L()   	GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define LCD_DC_H()   	GPIO_SetBits(GPIOA,GPIO_Pin_2)
 		     
#define LCD_CS_L()   	GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define LCD_CS_H()   	GPIO_SetBits(GPIOA,GPIO_Pin_3)

#define LCD_BLK_OFF()	GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define LCD_BLK_ON()	GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define CMD				0
#define DATA			1

#define CMD_READY		LCD_DC_L()
#define DAT_READY		LCD_DC_H()

#define SEND_START		LCD_CS_L()
#define SEND_END		LCD_CS_H()


/*
 * 0: portrait screen
 * 1: U - D invert
 * 2: L - R invert
 * 3: U-D & L-R invert
 *
 * 4: landscape screen
 * 5: U - D invert
 * 6: L - R invert
 * 7: U-D & L-R invert
 */
#define USE_HORIZONTAL 5

#if (USE_HORIZONTAL >= 0 && USE_HORIZONTAL <= 3) 
	#define SCREEN_W	80
	#define SCREEN_H	160
#else
	#define SCREEN_W	160
	#define SCREEN_H	80
#endif


#define BLACK    	0x0000	//	��ɫ    
#define NAVY     	0x000F	//	����ɫ  
#define DGREEN   	0x03E0	//  ����ɫ  
#define DCYAN    	0x03EF	//	����ɫ  
#define MAROON   	0x7800	//	���ɫ      
#define PURPLE   	0x780F	//	��ɫ  
#define OLIVE    	0x7BE0	//	�����      
#define LGRAY    	0xC618	//  �Ұ�ɫ
#define DGRAY    	0x7BEF	//  ���ɫ      
#define BLUE     	0x001F	//  ��ɫ    
#define GREEN    	0x07E0	//  ��ɫ          
#define CYAN     	0x07FF	//  ��ɫ  
#define RED      	0xF800	//  ��ɫ       
#define MAGENTA  	0xF81F	//  Ʒ��    
#define YELLOW   	0xFFE0	//  ��ɫ        
#define WHITE    	0xFFFF	//  ��ɫ
#define GRED 		0XFFE0
#define BRRED		0XFC07 //�غ�ɫ
#define INIT_FILL	BLACK



void lcd_init(void);
void lcd_DMAFill(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint16_t *fill_color, uint32_t DMA_MemoryInc);
void lcd_DMAFill_Picture(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, const uint8_t *pdata);
void lcd_Fill(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint16_t fill_color);

void lcd_DrawPoint(int x,int y,uint16_t color);
void lcd_DrawLine(int x1,int y1,int x2,int y2,uint16_t color);
void lcd_DrawRect(int left,int top,int width,int height, uint16_t color);
void lcd_DrawFastHLine(int x, int y, int w, uint16_t color);
void lcd_DrawFastVLine(int x, int y, int h, uint16_t color);
void lcd_DrawCircleHelper(int x0, int y0, int r, uint8_t cornername, uint16_t color);
void lcd_DrawRoundRect(int x, int y, int w, int h, int r, uint16_t color);
void lcd_DrawEllipse(int xCenter,int yCenter,int Rx,int Ry, uint16_t color);
void lcd_DrawCircle(int x,int y,int r,uint16_t color);
void lcd_DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint16_t color);

void lcd_show_char(uint16_t x, uint16_t y, uint8_t _char, uint8_t size, uint16_t color);
void lcd_show_str(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *string, uint16_t color);
void lcd_show_num(uint16_t x, uint16_t y, uint8_t size, float num, uint8_t res, uint16_t color);

void lcd_test(uint16_t color);


extern uint8_t DMA_Finish;


#endif
