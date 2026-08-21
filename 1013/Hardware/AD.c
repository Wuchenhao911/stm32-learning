#include "stm32f10x.h"                  // Device header
void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(6);//12MHz
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_Init_Structure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_Init_Structure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	
	ADC_InitTypeDef ADC_Init_Structure;
	ADC_Init_Structure.ADC_ScanConvMode=DISABLE;
	ADC_Init_Structure.ADC_ContinuousConvMode=ENABLE;
	ADC_Init_Structure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_Init_Structure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_Init_Structure.ADC_Mode=ADC_Mode_Independent;
	ADC_Init_Structure.ADC_NbrOfChannel=1;
	ADC_Init(ADC1,&ADC_Init_Structure);
	
	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)==SET);
	
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	return ADC_GetConversionValue(ADC1);
}

