#ifndef __OLED_H
#define __OLED_H 
#include "stm32f10x.h"


#define USE_DMA
#define USE_HARD_I2C


/* use I2C */
#ifdef USE_HARD_I2C
	#define I2C_SPEED		400000 /* SPEED */
	void i2c_init(void);
	void oled_send_cmd(uint8_t cmd);
#endif


/* use DMA */
#ifdef USE_DMA
	#define DMA_CIRCULAR	((uint32_t)0x00000020)
	#define DMA_NORMAL		((uint32_t)0x00000000)
	#define DMA_MODE		DMA_CIRCULAR /* DMA MODE */
	extern uint8_t DMA_working;
#endif


#define OLED_H	64
#define OLED_W	128

#define OLED_ADDR		0x78 /* OLED ADDR */

#define OLED_CMD  		0x00 /* CMD */
#define OLED_DATA 		0x40 /* DATA */

#define OLED_WR_CMD(x)	oled_send_cmd(x)




void OLED_Set_Contrast(uint8_t level);
void OLED_Set_Disp_Mode(uint8_t mode1, uint8_t mode2);
void OLED_On(void);
void OLED_Off(void);
void OLED_UD_Turn(uint8_t state);
void OLED_LR_Turn(uint8_t state);
void OLED_Set_Memory_Addr_Mode(uint8_t mode);
void OLED_Set_Colu_Start_Addr(uint8_t addr);
void OLED_Set_Page_Start_Addr(uint8_t page);
void OLED_Set_Colu_Range(uint8_t start, uint8_t end);
void OLED_Set_Page_Range(uint8_t start, uint8_t end);
void OLED_Set_Start_Line(uint8_t line);
void OLED_LR_Scroll(uint8_t page_start, uint8_t page_end, uint8_t dir, uint8_t speed);
void OLED_Scroll_On(void);
void OLED_Scroll_Off(void);

void oled_init(void);

void OLED_Fill(void);
void OLED_Refresh(void);
void OLED_Refresh_Picture(const uint8_t *BMP);
void OLED_Clear_GRAM(void);
void OLED_DrawPoint(int x,int y);
void OLED_ClearPoint(int x,int y);
void OLED_DrawLine(int x1,int y1,int x2,int y2);
void OLED_DrawRect(int left,int top,int width,int height);
void OLED_DrawFastHLine(int x, int y, uint8_t w);
void OLED_DrawFastVLine(int x, int y, uint8_t h);
void OLED_DrawCircleHelper(int x0, int y0, uint8_t r, uint8_t cornername);
void OLED_DrawRoundRect(int x, int y, uint8_t w, uint8_t h, uint8_t r);
void OLED_DrawEllipse(int xCenter,int yCenter,int Rx,int Ry);
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r);
void OLED_DrawTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

void oled_show_char(uint16_t x, uint16_t y, uint8_t _char, uint8_t size);
void oled_show_str(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *string);
void oled_show_num(uint16_t x, uint16_t y, uint8_t size, float num, uint8_t res);




/*************************************************待整理*******************************************/
/*************************************************待整理*******************************************/
/*************************************************待整理*******************************************/
void wave(uint8_t *buf, int val);
int my_printf(const char *str,...);
void printc(uint16_t x, uint16_t y, uint8_t ch,uint8_t size);
void OLED_DrawArc(int x,int y,unsigned char r,int angle_start,int angle_end);
void OLED_ShowStars(void);
void OLED_ShowWatch(void);
void OLED_ShowTest(void);
void oled_test(void);



#endif

