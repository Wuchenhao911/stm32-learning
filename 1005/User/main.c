#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "encoder.h"
int main()
{
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1,1,"Count");
	while(1)
	{
		OLED_ShowNum(1,7,get_encoder(),4);
	}
}
