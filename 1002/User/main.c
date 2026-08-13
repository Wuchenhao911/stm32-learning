#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Led.h"
#include "Key.h"

unsigned char Key_Down;

int main()
{
	Led_Init();
	Key_Init();
	while(1)
	{
		Key_Down=Key_Read();
		if(Key_Down==0x01)
			Led_Set();
		else if(Key_Down==0x02)
			Led_Reset();
	
	}
}
