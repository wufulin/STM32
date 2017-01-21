#ifndef __BREATHING_H
#define __BREATHING_H

#include "stm32f10x.h"

void TIM3_PWM_Init(void);
void TIM3_GPIO_Config(void);
void TIM3_Mode_Config(void);
void NVIC_Config_PWM(void);
void Update_TIM3_CCR(void);

#endif /* __BREATHING_H */
/*************************END OF FILE**********************/
