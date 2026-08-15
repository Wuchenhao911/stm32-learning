#include "stm32f10x.h" // Device header
int encoder_count;
void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_Structure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	EXTI_InitTypeDef EXTI_Init_Structure;
	EXTI_Init_Structure.EXTI_Line=EXTI_Line1|EXTI_Line0;
	EXTI_Init_Structure.EXTI_LineCmd=ENABLE;
	EXTI_Init_Structure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Init_Structure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Init_Structure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Init_Structure;
	NVIC_Init_Structure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_Init_Structure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Init_Structure.NVIC_IRQChannelSubPriority=1;
	
	NVIC_Init(&NVIC_Init_Structure);
	
	NVIC_Init_Structure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_Init_Structure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Init_Structure.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_Init_Structure);
}
int get_encoder(void)
{
	return encoder_count;
}
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line0);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		{
			encoder_count--;
		}
	}
	
}
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)==SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line1);
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
		{
			encoder_count++;
		}
	}
	
}
