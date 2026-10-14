#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "Project.h"
uint16_t AD_Value;

int main(void)
{
    OLED_Init();
		AD_Init();
    App_Init();
	g_sensor.light=123;
		OLED_ShowNum(1,1,g_sensor.light,3);
    while (1)
    {
			
    }
}
