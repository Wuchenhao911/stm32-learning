#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"
#include "OLED.H"
unsigned char Key_Down;

int main()
{
	OLED_Init();
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(3,3,"HELLOWORLD");
	while(1)
	{
		
	}
}
