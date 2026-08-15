#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.H"
#include "Timer.H"
unsigned int Num;
int main()
{
	OLED_Init();
	Timer_Init();
	while(1)
	{
		OLED_ShowNum(1,1,Num,4);
	}
}
