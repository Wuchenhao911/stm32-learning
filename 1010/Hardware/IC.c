#include "stm32f10x.h"                  // Device header
void IC_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_6;
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef Tim_Base_Init_Structure;
	Tim_Base_Init_Structure.TIM_ClockDivision=TIM_CKD_DIV1;
	Tim_Base_Init_Structure.TIM_CounterMode=TIM_CounterMode_Up;
	Tim_Base_Init_Structure.TIM_Period=65536-1;//ARR
	Tim_Base_Init_Structure.TIM_Prescaler=72-1;//PSC
	Tim_Base_Init_Structure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&Tim_Base_Init_Structure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter=0xF;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	TIM_Cmd(TIM3,ENABLE);
	
}
uint32_t IC_GetFreq(void)
{
	return 1000000/TIM_GetCapture1(TIM3);
}
uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1);
}
