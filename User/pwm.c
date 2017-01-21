/**
  ******************************************************************************
  * @file   
  * @author  wufulin
  * @version v1.0
  * @date    2016-06-11
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "pwm.h"

/**
  * @brief  TIM3 输出PWM信号初始化函数
  * @param  
  * @retval 无
  */
  void TIMx_PWM_Init(void)
  {
  	TIMx_GPIO_Config();
  	TIMx_Mode_Config();
  }

/**
  * @brief  配置 TIM3 复用输出 PWM 时用到的 I/O
  * @param  
  * @retval 无
  */
  void TIMx_GPIO_Config(void)
  {
  	GPIO_InitTypeDef GPIO_InitStructure;
  	/* 设置 TIM3CLK 为 72MHZ */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  	/*开启GPIOA、GPIOB的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	// 配置TIM3的GPIOA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 配置TIM3的GPIOB
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  }

/**
  * @brief 配置 TIM3 输出的 PWM 信号的模式，如周期、极性、占空比
  * @param  
  * @retval 无
  *
  * 信号周期=(TIMx_ARR+1)*时钟周期
  * 占空比=TIMx_CCR/(TIMx_ARR+1)
  */
  void TIMx_Mode_Config(void)
  {
  	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  	TIM_OCInitTypeDef TIM_OCInitStructure;

  	uint16_t CCR1_Val = 500;
  	uint16_t CCR2_Val = 375;
  	uint16_t CCR3_Val = 250;
  	uint16_t CCR4_Val = 125;

  	TIM_TimeBaseStructure.TIM_Period = 1000; // 定时周期
  	TIM_TimeBaseStructure.TIM_Prescaler = 0; // 设置预分频，这里不分频
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 设置时钟分频系数
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
		// PWM1 配置 Channel 1
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // 配置为PWM模式1
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = CCR1_Val; // 设置跳变值
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 小于CCR1_Val时为高电平
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); // 使能通道1
		
		// PWM1 配置 Channel 2
		TIM_OCInitStructure.TIM_Pulse = CCR2_Val; // 设置跳变值
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); // 使能通道2
		
		// PWM1 配置 Channel 3
		TIM_OCInitStructure.TIM_Pulse = CCR3_Val; // 设置跳变值
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); // 使能通道3
		
		// PWM1 配置 Channel 4
		TIM_OCInitStructure.TIM_Pulse = CCR4_Val; // 设置跳变值
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); // 使能通道4
		
		// 使能TIM3重载寄存器ARR
		TIM_ARRPreloadConfig(TIM3, ENABLE);

  	// 使能定时器3
  	TIM_Cmd(TIM3, ENABLE);
  }
/**************************END OF FILE**********************/
