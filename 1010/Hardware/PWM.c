#include "stm32f10x.h"                  // Device header


void PWM_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef Tim_Base_Init_Structure;
	Tim_Base_Init_Structure.TIM_ClockDivision=TIM_CKD_DIV1;
	Tim_Base_Init_Structure.TIM_CounterMode=TIM_CounterMode_Up;
	Tim_Base_Init_Structure.TIM_Period=100-1;//ARR
	Tim_Base_Init_Structure.TIM_Prescaler=720-1;//PSC
	Tim_Base_Init_Structure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&Tim_Base_Init_Structure);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM2,ENABLE);
	
	TIM_OCInitTypeDef TIM_OCInit_Structure;
	TIM_OCStructInit(&TIM_OCInit_Structure);
	TIM_OCInit_Structure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInit_Structure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInit_Structure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInit_Structure.TIM_Pulse=0;//CCR
	TIM_OC1Init(TIM2,&TIM_OCInit_Structure);
	
	
}

void PWM_SetComparel(unsigned int Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}

void PWM_SetPrescaler(unsigned int Prescaler)
{
	TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Update);
}
