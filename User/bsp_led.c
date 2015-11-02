/**
  ******************************************************************************
  * @file   led.c
  * @author  wufulin
  * @version v1.0
  * @date    2015-10-21
  * @brief   led 应用函数库
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "bsp_led.h"

/**
  * @brief  配置LED用到的I/O口
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef 类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启GPIOB、GPIOD的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD, ENABLE);
	
	/*选择要控制的GPIOC引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	/*设置引脚速率为50MHz*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*调用库函数，初始化GPIOD*/
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/*调用库函数，初始化GPIOB*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*关闭所有led灯*/
	GPIO_ResetBits(GPIOD, GPIO_Pin_3 | GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}
/*********************************************END OF FILE**********************/
