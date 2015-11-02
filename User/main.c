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
#include "bsp_led.h"
#include "tool.h"


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/* USART1 config 115200 8-N-1 */
	USART1_Config();
	
	LED_GPIO_Config();	
	
	printf("\r\n this is a printf demo \r\n");
//	scanf("\r\n 欢迎使用野火M3实验板 \r\n");
	
	for(;;)
	{
		printf("\r\n this is a printf demo \r\n");
		
		LED3(OFF); LED1(ON); LED2(OFF);			// 亮
		Delay(0xAFFFEF);	
		//LED1(OFF);          // 灭
		
		LED1(OFF); LED2(ON); LED3(OFF);
		Delay(0xAFFFEF);
		//LED2(OFF);
		
		LED2(OFF); LED3(ON); LED1(OFF); 
		Delay(0xAFFFEF);
		//LED3(OFF);	
		
		//scanf("\r\n 123 \r\n");		
	}
}

/*********************************************END OF FILE**********************/
