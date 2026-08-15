#include "stm32f10x.h" 
#include "Delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启时钟
	GPIO_InitTypeDef GPIOB_Init_Structure;
	GPIOB_Init_Structure.GPIO_Mode=GPIO_Mode_IPU;
	GPIOB_Init_Structure.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_5;
	GPIOB_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOB_Init_Structure);//GPIOA初始化
}
unsigned char Key_Read(void)
{
	unsigned char temp=0x00;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0);
		Delay_ms(20);
		temp=0x01;
	}
	else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0);
		Delay_ms(20);
		temp=0x02;
	}
	
	return temp;
}
