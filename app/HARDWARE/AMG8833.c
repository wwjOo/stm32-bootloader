#include "AMG8833.h"
#include "delay.h"

#define TIME	2

/*
 * GPIO init
 */
void I2C_Soft_Init(void)
{
	/* GPIO */
	GPIO_InitTypeDef GPIO_InitStruct;
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_0|GPIO_Pin_1;	 
 	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	SCL_H;
	SDA_H;
}

/*
 * start
 */
void I2C_Soft_Start(void)
{
	SDA_OUT;
	
	SDA_H; 	
	delay_us(TIME);  
	SCL_H;
	delay_us(TIME);
	
 	SDA_L;
	delay_us(TIME);
	SCL_L;
	delay_us(TIME);
}

/*
 * stop
 */
void I2C_Soft_Stop(void)
{
	SDA_OUT;
	
	SCL_L;
	delay_us(TIME);
	SDA_L;
 	delay_us(TIME);
	
	SCL_H; 
	delay_us(TIME);
	SDA_H;
	delay_us(TIME);						   	
}

/*
 * wait ack
 */
uint8_t I2C_Soft_WaitAck(void)
{
	SDA_IN; 
	
	SDA_H;
	delay_us(TIME);
	SCL_H;
	delay_us(TIME);
	
	delay_us(TIME);
	if( SDA_STATE == 1 )
	{
		I2C_Soft_Stop();
		return 1;
	}
	
	SCL_L;  
	delay_us(TIME);	
	
	return 0;  
} 


/*
 * send ack
 */
void I2C_Soft_Ack(void)
{
	SCL_L;
	SDA_OUT;
	
	SDA_L;
	delay_us(TIME);
	
	SCL_H;
	delay_us(TIME);
	SCL_L;
}


/*
 * send no ack
 */	    
void I2C_Soft_NoAck(void)
{
	SCL_L;
	SDA_OUT;
	
	SDA_H;
	delay_us(TIME);
	
	SCL_H;
	delay_us(TIME);
	SCL_L;
}			

/*
 * send byte
 */
void I2C_Soft_SendByte(uint8_t data)
{                        
    uint8_t i;   
	
	SDA_OUT; 
	
    for(i=0; i<8; i++)
    {          
		SCL_L;	
		delay_us(TIME);    
		
		if((data&0x80)>>7)
			SDA_H;
		else
			SDA_L;
		data<<=1; 			
		delay_us(TIME);
		
		SCL_H;
		delay_us(TIME); 
    }	
	
    SCL_L; 
} 	    

/*
 * read byte
 */
uint8_t I2C_Soft_ReadByte(uint8_t Ack)
{
	uint8_t i,receive=0;
	SDA_IN;
	
    for(i=0; i<8; i++)
	{
        SCL_L; 
        delay_us(TIME);
		SCL_H;
        receive <<= 1;
		
        if(SDA_STATE)
			receive++;
		delay_us(TIME);
    }
	
    if (!Ack)
        I2C_Soft_NoAck();
    else
        I2C_Soft_Ack();
	
    return receive;
}



/*******************************/
/*******************************/
/*******************************/
/*
 * init
 */
void AMG88xx_Init(void)
{
	/* soft i2c */
	I2C_Soft_Init();
	
	I2C_Soft_Start();
	I2C_Soft_SendByte(0xD2);
	if(I2C_Soft_WaitAck())return;
	I2C_Soft_SendByte(0x00);
	if(I2C_Soft_WaitAck())return;
	I2C_Soft_SendByte(0x00);
	if(I2C_Soft_WaitAck())return;
	I2C_Soft_Stop();
	delay_ms(10);
	I2C_Soft_Start();
	I2C_Soft_SendByte(0xD2);
	if(I2C_Soft_WaitAck())return;
	I2C_Soft_SendByte(0x01);
	if(I2C_Soft_WaitAck())return;
	I2C_Soft_SendByte(0x3f);
	if(I2C_Soft_WaitAck())return;
	I2C_Soft_Stop();
	delay_ms(10);
	I2C_Soft_Start();
	I2C_Soft_SendByte(0xD2);
	if(I2C_Soft_WaitAck())return;
	I2C_Soft_SendByte(0x02);
	if(I2C_Soft_WaitAck())return;
	I2C_Soft_SendByte(0x00);
	if(I2C_Soft_WaitAck())return;
	I2C_Soft_Stop();

	delay_ms(50);
}


/*
 * AMG read
 */
#include "string.h"
uint16_t AMG_Buf[64];

void AMG88xx_read(void)
{
	/* maximum frame rate of 10Hz */
	
	u8 i;
	uint8_t read_buf[128];
	
	/* send cmd */
	I2C_Soft_Start(); 
	I2C_Soft_SendByte(AMG_ADDR);
	if(I2C_Soft_WaitAck())
		return;
	I2C_Soft_SendByte(0X80);
	if(I2C_Soft_WaitAck())
		return;

	/* read */
	I2C_Soft_Start();
	I2C_Soft_SendByte(AMG_ADDR|0x01);
	if(I2C_Soft_WaitAck())
		return;
	for(i=0; i<128; i++)
		read_buf[i]=I2C_Soft_ReadByte(!(i/127));
	
	/* over */
	I2C_Soft_Stop();
	
	memcpy(AMG_Buf, read_buf, sizeof(AMG_Buf));
	
	for(i=0; i<64; i++)
	{
		if(AMG_Buf[i] < 100)
			AMG_Buf[i] = 0;
		
//		if(temp[i] > 29)
//			AMG_Buf[i] = 0x000F;
//		else if(temp[i] > 30)
//			AMG_Buf[i] = 0x0FF0;
//		else if(temp[i] > 29)
//			AMG_Buf[i] = 0xF000;
//		else
//			AMG_Buf[i] = 0x0000;
	}
}


