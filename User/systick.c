/**
	******************************************************************************
	* @file	 systick.c
	* @author	wufulin
	* @version v1.0
	* @date		2016-6-10
	* @brief	 SysTick 系统定时器
	******************************************************************************
	* @attention
	*
	*
	******************************************************************************
	*/
#include "systick.h"

static __IO uint32_t TimingDelay;

/**
	* @brief	初始化系统滴答定时器 SysTick
	* @param	无
	* @retval 无
	*/
	void SysTick_Init(void)
	{
		// 1 = failed, 0 = successful
		if(SysTick_Config(ONE_MS_TICKS)){
			// capture error
			while(1);
		}
		// 关闭滴答定时器
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	}
	
	/**
	* @brief	延时程序，1ms为一个单位
	* @param	nTime延时时间
	* @retval 无
	*/
	void Delay_ms(__IO uint32_t nTime)
	{
		TimingDelay = nTime;
		
		// 使能滴答定时器
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
		
		while(TimingDelay !=0);
	}
	
	/**
	* @brief	获取节拍程序, 在 SysTick 中断函数 SysTick_Handler()调用
	* @param	无
	* @retval 无
	*/
	void TimingDelay_Decrement(void)
	{
		if(TimingDelay != 0x00){
			TimingDelay--;
		}
	}
	/*********************************************END OF FILE**********************/
	