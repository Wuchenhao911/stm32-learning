#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
uint16_t AD0;
uint16_t AD1;
uint16_t AD2;
uint16_t AD3;
float Voltage;
int main(void)
{
	AD_Init();
	OLED_Init();
	
	while (1)
	{
		AD0=AD_GetValue(ADC_Channel_0);
		AD1=AD_GetValue(ADC_Channel_1);
		AD2=AD_GetValue(ADC_Channel_2);
		AD3=AD_GetValue(ADC_Channel_3);
		OLED_ShowNum(1,5,AD0,4);
		OLED_ShowNum(2,5,AD1,4);
		OLED_ShowNum(3,5,AD2,4);
		OLED_ShowNum(4,5,AD3,4);
		Delay_ms(100);
	}
}
