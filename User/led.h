#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

/** the macro definition to trigger the led on or off
 * 1 - off
 * 0 - on
 */
#define ON	1
#define OFF 0

// 带参宏，可以像内联函数一样使用 GPIO_SetBits引脚置1函数 GPIO_ResetBits引脚清零函数
#define LED1(a) if (a) \
					GPIO_ResetBits(GPIOB, GPIO_Pin_0);\
					else \
					GPIO_SetBits(GPIOB, GPIO_Pin_0);

#define LED2(a) if (a) \
					GPIO_ResetBits(GPIOF, GPIO_Pin_7);\
					else \
					GPIO_SetBits(GPIOF, GPIO_Pin_7);
					
#define LED3(a) if (a) \
					GPIO_ResetBits(GPIOF, GPIO_Pin_8);\
					else \
					GPIO_SetBits(GPIOF, GPIO_Pin_8);

					
void LED_GPIO_Config(void);

#endif /* __LED_H */

/*********************************************END OF FILE**********************/

