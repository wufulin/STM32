#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

#define ONE_MS_TICKS (SystemCoreClock/1000)         //	1ms
#define ONE_US_TICKS (SystemCoreClock/1000000)			//	1us

void SysTick_Init(void);
void Delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

#endif /* __SYSTICK_H */	

/*********************************************END OF FILE**********************/
