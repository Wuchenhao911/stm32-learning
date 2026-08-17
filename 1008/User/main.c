#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Servo.h"
#include "Key.h"
unsigned char i;
unsigned char key_num;
int main(void)
{
						
	OLED_Init();
	PWM_Init();
	Key_Init();
	Servo_control(0);
	
	while (1)
	{
		OLED_ShowNum(2, 1, GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1), 1);  // 探测
		key_num=Key_GetNum();
		if(key_num==1)
		{
			i+=1;
			if(i>3)
				i=0;
			Servo_control(i);
		}
		OLED_ShowNum(1,1,i,1);
	}
}
