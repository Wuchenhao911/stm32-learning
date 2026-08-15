#include "stm32f10x.h"
unsigned int Counter_Sensor_Count=0;
void CounterSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启AFIO时钟
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_14;
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_Structure);//GPIO初始化
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	EXTI_InitTypeDef EXTI_Init_Structure;
	EXTI_Init_Structure.EXTI_Line=EXTI_Line14;
	EXTI_Init_Structure.EXTI_LineCmd=ENABLE;
	EXTI_Init_Structure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Init_Structure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Init_Structure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Init_Structure;
	NVIC_Init_Structure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_Init_Structure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Init_Structure.NVIC_IRQChannelSubPriority=1;
	
	NVIC_Init(&NVIC_Init_Structure);
}
unsigned int Count_Sensor_Get(void)
{
	return Counter_Sensor_Count;
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line14);
		Counter_Sensor_Count++;
	}
}
