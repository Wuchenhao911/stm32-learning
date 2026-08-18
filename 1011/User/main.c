#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"
uint16_t Num;
int main(void)
{
	OLED_Init();
//	Timer_Init();
	Encoder_Init();
	OLED_ShowString(1, 1, "Num:");
	
	while (1)
	{
		OLED_ShowSignedNum(1, 5, Encoder_Get(), 5);
		Delay_ms(1000);
	}
}

//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//	{
//		Num ++;
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}
