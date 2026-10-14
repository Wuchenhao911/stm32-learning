#include "stm32f10x.h"  
#include "Project.h"
#include "AD.h"
SensorData_t g_sensor;
Config_t g_config;
void App_Init(void)
{
	uint8_t i;
	g_sensor.count=0;
	g_sensor.light=0;
	g_sensor.pitch=0;
	g_sensor.pot=0;
	g_sensor.roll=0;
	g_sensor.temp=0;
	for(i=0;i<4;i++)
	{
		g_sensor.ad_raw[i]=0;
		g_sensor.voltage[i]=0.0f;
	}
	g_config.fan_on=0;
	g_config.light_alarm=20.0f;
	g_config.temp_alarm=30.0f;
}
/* 把硬件层的 AD_Value[0..3] 一次性搬进 App 层档案 g_sensor */
void App_Update(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		g_sensor.ad_raw[i]=AD_Value[i];
		g_sensor.voltage[i]=App_GetVoltage(i);
	}
	g_sensor.pot=App_GetPotPercent();
	g_sensor.light=g_sensor.voltage[1];
}

float App_GetVoltage(uint8_t ch)
{
	if(ch>3) return 0.0f;
	return AD_Value[ch]*3.3f/4095.0f;
}
float App_GetPotPercent(void)
{
	return AD_Value[0]*100.0f/4095.0;
}
