#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"

/** the macro definition to trigger the led on or off
 * 1 - off
 * 0 - on
 */
#define ON	1
#define OFF 0

// 带参宏，可以像内联函数一样使用 GPIO_SetBits引脚置1函数 GPIO_ResetBits引脚清零函数
#define BEEP(a) if (a) \
					GPIO_SetBits(GPIOC, GPIO_Pin_0);\
					else \
					GPIO_ResetBits(GPIOC, GPIO_Pin_0);

void Beep_GPIO_Config(void);

#endif /* __BEEP_H */

/*********************************************END OF FILE**********************/
