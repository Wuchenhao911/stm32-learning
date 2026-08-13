#include "stm32f10x.h"  

void Led_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	GPIO_InitTypeDef GPIOA_Init_Structure;
	GPIOA_Init_Structure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOA_Init_Structure.GPIO_Pin=GPIO_Pin_4;
	GPIOA_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_Init_Structure);//GPIOA初始化
}

void Led_Set(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}

void Led_Reset(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}
