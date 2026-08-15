#ifndef __ENCODER_H
#define __ENCODER_H
void Encoder_Init(void);
int get_encoder(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
#endif
