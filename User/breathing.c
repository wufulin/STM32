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
#include "breathing.h"

static uint8_t indexWave[] = {1,1,2,2,3,4,6,8,10,14,19,25,33,44,59,80,107,143,
191,255,255,191,143,107,80,59,44,33,25,19,14,10,8,6,4,3,2,2,1,1};

static uint16_t Duty[] = {1800,1856,1912,1968,2023,2078,2131,2183,2233,2282,2329,2373,2416,2456,2493,  
    2528,2559,2588,2614,2636,2655,2671,2684,2692,2698,2699,2698,2692,2684,2671,2655,2636,2614,  
    2588,2559,2528,2493,2456,2416,2373,2329,2282,2233,2183,2131,2078,2023,1968,1912,1856,1800,  
    1743,1687,1631,1576,1521,1468,1416,1366,1317,1270,1226,1183,1143,1106,1071,1040,1011,985,  
    963,944,928,915,907,901,900,901,907,915,928,944,963,985,1011,1040,1071,1106,1143,1183,1226,  
    1270,1317,1366,1416,1468,1521,1576,1631,1687,1743,1799,1799};  

		
/**
  * @brief  TIM3 呼吸灯初始化，配置PWM模式和GPIO
  * @param  
  * @retval 无
  */
  void TIM3_PWM_Init(void)
  {
  	TIM3_GPIO_Config();
  	TIM3_Mode_Config();
  }

/**
  * @brief  配置 TIM3 复用输出 PWM 时用到的 I/O
  * @param  
  * @retval 无
  */
  void TIM3_GPIO_Config(void)
  {
  	GPIO_InitTypeDef GPIO_InitStructure;
  	/* 设置 TIM3CLK 为 72MHZ */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  	/*开启GPIOA、GPIOB的外设时钟*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

		// 配置TIM3的GPIOB
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
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
  void TIM3_Mode_Config(void)
  {
  	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  	TIM_OCInitTypeDef TIM_OCInitStructure;

  	TIM_TimeBaseStructure.TIM_Period = 255; // 定时周期
  	TIM_TimeBaseStructure.TIM_Prescaler = 1999; // 设置预分频
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 设置时钟分频系数
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
		// PWM1 配置 Channel 3
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // 配置为PWM模式1
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0; // 设置跳变值
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; // 小于CCR3_Val时为低电平
		TIM_OC3Init(TIM3, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); // 使能通道3
		
		// 使能TIM3重载寄存器ARR
		TIM_ARRPreloadConfig(TIM3, ENABLE);

  	// 使能定时器3
  	TIM_Cmd(TIM3, ENABLE);
		
		// 配置定时器更新中断
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
		NVIC_Config_PWM();
  }
	
	/**
	 * @brief 配置嵌套向量中断控制器 NVIC
	 * @param  无
	 * @retval 无
	 */
	void NVIC_Config_PWM(void)
	{
		NVIC_InitTypeDef NVIC_InitStructure;
  
		/* Configure one bit for preemption priority */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
	}
	
	/**
	 * @brief 呼吸灯中断服务函数
	 * @param  无
	 * @retval 无
	 */
	void Update_TIM3_CCR()
	{
		static uint8_t pwm_index = 0;
		static uint8_t period_count = 0;
		static uint8_t count = 0;  
    static uint8_t num = sizeof(Duty)/(sizeof(Duty[0]));  
		
		if(TIM_GetITStatus(TIM3, TIM_IT_Update)!= RESET){
			// TIM_IT_Update
			period_count++;
			if(period_count >= 10){
				TIM3->CCR3 = indexWave[pwm_index];
				pwm_index++;
				if(pwm_index >= 40){
					pwm_index = 0;
				}
				period_count = 0;
			}
			//TIM3->SR = (uint16_t)~TIM_IT_CC3;  
//			TIM3->CCR3 = Duty[count];  
//			count++;  
//			if(count==num)  
//			{  
//					count=0;  
//			}  
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		
	}
/**************************END OF FILE**********************/
