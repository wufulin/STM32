/**
  ******************************************************************************
  * @file   beep.c
  * @author  wufulin
  * @version v1.0
  * @date    2016-1-12
  * @brief   beep 蜂鸣器应用函数库
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "beep.h"

/**
  * @brief  配置beep蜂鸣器用到的I/O口
  * @param  无
  * @retval 无
  */
void Beep_GPIO_Config(void)
{
    /*定义一个GPIO_InitTypeDef 类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启GPIOC的外设时钟*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);

    /*选择要控制的GPIOC引脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;

    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    /*设置引脚速率为50MHz*/
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    /*调用库函数，初始化GPIOC*/
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /*关闭beep蜂鸣器输出*/
    GPIO_ResetBits(GPIOC, GPIO_Pin_0);
}
/*********************************************END OF FILE**********************/
