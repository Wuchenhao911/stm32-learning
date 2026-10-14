#ifndef __PROJECT_H
#define __PROJECT_H
typedef struct
{
	float temp;//温度数据
	float light;//光照数据
	float pot;//电位器位置
	float pitch,roll;//互补滤波后的姿态角
	uint16_t count;//物体技术
}SensorData_t;
typedef struct
{
	float temp_alarm;//温度报警阈值
	float light_alarm;//光照报警阈值
	uint8_t fan_on;//风扇开关
	
}Config_t;
extern SensorData_t g_sensor;
extern Config_t g_config;
void App_Init(void);
#endif
