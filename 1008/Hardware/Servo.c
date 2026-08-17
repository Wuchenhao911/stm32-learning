#include "stm32f10x.h"   // Device header
#include "PWM.h"
void Servo_control(unsigned char state)
{
	switch(state)
	{
		case 0://0
			PWM_SetCompare2(500);
		break;
		case 1://0
			PWM_SetCompare2(1000);
		break;
		case 2://0
			PWM_SetCompare2(1500);
		break;
		case 3://0
			PWM_SetCompare2(2000);
		break;
		
	}
	
}
