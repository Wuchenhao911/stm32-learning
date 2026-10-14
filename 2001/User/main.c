#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "Project.h"
#include "Serial.h"

int main(void)
{
	OLED_Init();
	AD_Init();
	App_Init();
	Serial_Init();
	while (1)
	{
		App_Update();
		Delay_ms(1000);
	}
}
