#include "stm32f10x.h"                  // Device header
#include "OLED_Font.h"
#define OLED_W_SCL(x) GPIO_WriteBit(GPIOB,GPIO_Pin_8,(BitAction)(x));
#define OLED_W_SDA(x) GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(x));
void OLED_I2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}
void OLED_Send_Byte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		OLED_W_SDA(Byte&(0x80>>i));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);
	OLED_W_SCL(0);
}
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_Send_Byte(0x78);
	OLED_Send_Byte(0x00);
	OLED_Send_Byte(Command);
	OLED_I2C_Stop();
}
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_Send_Byte(0x78);
	OLED_Send_Byte(0x40);
	OLED_Send_Byte(Data);
	OLED_I2C_Stop();
}
void OLED_SetCursor(uint8_t Y,uint8_t X)
{
	OLED_WriteCommand(0xB0|Y);
	OLED_WriteCommand(0x10|((X&0xF0)>>4));
	OLED_WriteCommand(0x00|(X&0x0F));
}
void OLED_Clear(void)
{
	uint8_t i,j;
	for(j=0;j<8;j++)
	{
		OLED_SetCursor(j,0);
		for(i=0;i<128;i++)
		{
			OLED_WriteData(0x00);
		}
	}
}
void OLED_Init(void)
{
    uint32_t i, j;

    for (i = 0; i < 1000; i++)              /* 上电稍等，等模块内部上电复位完成 */
    {
        for (j = 0; j < 1000; j++);
    }

    OLED_I2C_Init();                        /* 端口初始化 */

    OLED_WriteCommand(0xAE);                /* Set Display ON/OFF → AEh = 关闭显示 */

    OLED_WriteCommand(0xD5);                /* Set Display Clock Divide */
    OLED_WriteCommand(0x80);                /* 分频比 1、振荡频率 8（默认值） */

    OLED_WriteCommand(0xA8);                /* Set Multiplex Ratio */
    OLED_WriteCommand(0x3F);                /* 0x3F → 64 MUX（对应 64 行高） */

    OLED_WriteCommand(0xD3);                /* Set Display Offset */
    OLED_WriteCommand(0x00);                /* 无偏移 */

    OLED_WriteCommand(0x40);                /* Set Display Start Line = 0 */

    OLED_WriteCommand(0xA1);                /* Set Segment Re-map → A1h = 水平镜像（列方向） */

    OLED_WriteCommand(0xC8);                /* Set COM Scan Direction → C8h = 垂直镜像（行方向） */

    OLED_WriteCommand(0xDA);                /* Set COM Pins hardware config */
    OLED_WriteCommand(0x12);                /* A[4]=1 交替 COM 排列（0.96" 模块用这个） */

    OLED_WriteCommand(0x81);                /* Set Contrast Control */
    OLED_WriteCommand(0xCF);                /* 对比度 0xCF（越亮越大，范围 0x00~0xFF） */

    OLED_WriteCommand(0xD9);                /* Set Pre-charge Period */
    OLED_WriteCommand(0xF1);                /* 预充电周期 */

    OLED_WriteCommand(0xDB);                /* Set VCOMH Deselect Level */
    OLED_WriteCommand(0x30);                /* VCOMH 电平 */

    OLED_WriteCommand(0xA4);                /* Entire Display ON → A4h = 跟随显存内容（正常） */

    OLED_WriteCommand(0xA6);                /* Set Normal/Inverse → A6h = 正常显示（0 灭 1 亮） */

    OLED_WriteCommand(0x8D);                /* Charge Pump Setting */
    OLED_WriteCommand(0x14);                /* 开启电荷泵 → 芯片自己产生驱动 OLED 所需的高压 */

    OLED_WriteCommand(0xAF);                /* Set Display ON/OFF → AFh = 开启显示 */

    OLED_Clear();
}
void OLED_ShowChar(uint8_t Line,uint8_t Column,char Char)
{
	uint8_t i;
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);       /* 定位到上半页 */
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i]);
    }
    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);   /* 定位到下半页 */
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);
    }
}
void OLED_ShowString(uint8_t Line,uint8_t Column,char *String)
{
	uint8_t i;
	for(i=0;String[i]!='\0';i++)
	{
		OLED_ShowChar(Line,Column+i,String[i]);
	}
}
uint32_t OLED_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result=1;
	while(Y--)
	{
		Result *= X;
	}
  return	Result;
}
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		 OLED_ShowChar(Line, Column + i,
                      Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
    uint8_t i;
    uint32_t Number1;
    if (Number >= 0)
    {
        OLED_ShowChar(Line, Column, '+');
        Number1 = Number;
    }
    else
    {
        OLED_ShowChar(Line, Column, '-');
        Number1 = -Number;              /* 取绝对值 */
    }
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i + 1,     /* 注意 +1：给符号让位 */
                      Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i, SingleNumber;
    for (i = 0; i < Length; i++)
    {
        SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
        if (SingleNumber < 10)
        {
            OLED_ShowChar(Line, Column + i, SingleNumber + '0');        /* 0~9 */
        }
        else
        {
            OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');   /* 10~15 → A~F */
        }
    }
}
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i,
                      Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
    }
}
