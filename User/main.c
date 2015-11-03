/**
  ******************************************************************************
  * @file   
  * @author  wufulin
  * @version v1.0
  * @date    2015-10-27
  * @brief   串口通信
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "usart1.h"
#include "led.h"
#include "tool.h"
#include "key.h"


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/* USART1 config 115200 8-N-1 */
//	USART1_Config();
	
	LED_GPIO_Config();
	LED1(ON);	
	
	Key_GPIO_Config();
	
//	for(;;)
//	{	
//		LED3(OFF); LED1(ON); LED2(OFF);			// 亮
//		Delay(0xAFFFEF);	
//		
//		LED1(OFF); LED2(ON); LED3(OFF);
//		Delay(0xAFFFEF);
//		
//		LED2(OFF); LED3(ON); LED1(OFF); 
//		Delay(0xAFFFEF);	
//	}
	
	while(1){
		if(Key_Scan(GPIOA, GPIO_Pin_0) == KEY_ON){
			// LED1反转
			GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0))));
		}
	}
}

/*********************************************END OF FILE**********************/
