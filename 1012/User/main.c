#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
uint16_t AD;
float Voltage;
int main(void)
{
	AD_Init();
	OLED_Init();
	
	while (1)
	{
		AD=AD_GetValue();
		OLED_ShowNum(1,1,AD,4);
		Voltage=AD/4095.0*3.3;
		OLED_ShowNum(2,1,Voltage,1);
		OLED_ShowNum(2,2,((uint16_t)(Voltage*100)%100),2);

		
	}
}
