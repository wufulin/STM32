/**
  ******************************************************************************
  * @file    exit.c
  * @author  wufulin
  * @version v1.0
  * @date    2016-1-12
  * @brief   EXIT外部中断
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "exti.h"

/**
	* @brief 配置NVIC
	* @param 无
	* @retval 无
	*/
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	// 配置中断源
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; // EXTI0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
}

/**
	* @brief 配置PC13为线中断口，并设置中断优先级
	* @param 无
	* @retval 无
	*/
void EXTI_Pxy_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	// 配置GPIOC和AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE); // 需要配置AFIO时钟

	// 配置NVIC
	NVIC_Configuration();

	// 配置GPIOC端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// 配置EXTI输入线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure);
}
