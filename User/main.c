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
#include "beep.h"
#include "tool.h"
#include "key.h"
#include "exti.h"
#include "systick.h"
#include "pwm.h"
#include "breathing.h"
#include "dac.h"
#include <stdio.h>

extern uint8_t SendBuff[SENDBUFF_SIZE];

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	uint8_t i;
	for(i=0; i<SENDBUFF_SIZE; i++)
	{
		SendBuff[i] = 'A';
	}

	/* USART1 config 115200 8-N-1 */
	USART1_Config();
	USART1_DMA_Config();
	printf("\r\n 欢迎使用野火 iso STM32 开发板 \r\n");

	// USART1向DMA发出TX请求
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	
	//LED_GPIO_Config();
//	LED1(ON);	
	//Beep_GPIO_Config();
	//BEEP(ON);
	
	//Key_GPIO_Config();
	// EXTI_Pxy_Config();
	
	/* 配置 SysTick 为 1ms 中断一次 */
	SysTick_Init();
	
// 	for(;;)
// 	{	
// 		LED3(OFF); LED1(ON); LED2(OFF);			// 亮
// 		Delay(0xAFFFEF);	

// 		LED1(OFF); LED2(ON); LED3(OFF);
// 		Delay(0xAFFFEF);

// 		LED2(OFF); LED3(ON); LED1(OFF); 
// 		Delay(0xAFFFEF);	
// 	}
	
	//while(1){
		//if(Key_Scan(GPIOA, GPIO_Pin_0) == KEY_ON){
			// LED1反转
			//LED1_TOGGLE();
//			GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0))));
		//}
	//}
	
	//TIM3 PWM 波输出初始化，并使能 TIM3 PWM 输出
// 	TIM3_PWM_Init();
// 	while(1);

//	for(;;)
//	{
//		LED3(OFF);
//		LED1(ON);
//		Delay_ms(3000);
//		
//		LED1(OFF);
//		LED2(ON);
//		Delay_ms(1000);
//		
//		LED2(OFF);
//		LED3(ON);
//		Delay_ms(1000);
//	}

}

void DAC_RUN(void)
{
	/* 初始化DAC， 开始DAC转换 */
	DAC_Mode_Init();
	while(1);
}

/*********************************************END OF FILE**********************/
