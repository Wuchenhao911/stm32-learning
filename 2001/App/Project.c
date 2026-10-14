#include "stm32f10x.h"  
#include "Project.h"
SensorData_t g_sensor;
Config_t g_config;
void App_Init(void)
{
	g_sensor.count=0;
	g_sensor.light=0;
	g_sensor.pitch=0;
	g_sensor.pot=0;
	g_sensor.roll=0;
	g_sensor.temp=0;
	g_config.fan_on=0;
	g_config.light_alarm=20.0f;
	g_config.temp_alarm=30.0f;
}
