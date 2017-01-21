/**
  ******************************************************************************
  * @file   
  * @author  wufulin
  * @version v1.0
  * @date    2016-06-14
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#include "dac.h"

/*---------------------------- 波形数据 ----------------------------*/
const uint16_t Sine12bit[32] = {
  2448,2832,3186,3496,3751,3940,4057,4095,4057,3940,
  3751,3496,3186,2832,2448,2048,1648,1264,910,600,345,
  156,39,0,39,156,345,600,910,1264,1648,2048};

/*
 * @brief DAC初始化函数
 * @param 无
 * @retval 无
 */
void DAC_Mode_Init(void)
{
	uint32_t Idx = 0;
	
	DAC_Config();
	DAC_TIM_Config();
	DAC_DMA_Config();
	
	/* 填充正弦波形数据，双通道右对齐 */
	for(Idx = 0; Idx < 32; Idx++){
		//DualSine12bit[Idx] = (Sine12bit[Idx] << 16) + (Sine12bit[Idx]);
	}
}

/*
 * @brief 使能DAC时钟，初始化GPIO
 * @param 无
 * @retval 无
 */
void DAC_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;
	
	
	RCC_APB2Periph
}

/*
 * @brief DAC初始化函数
 * @param 无
 * @retval 无
 */
void DAC_TIM_Config()
{
}

/*
 * @brief DAC初始化函数
 * @param 无
 * @retval 无
 */
void DAC_DMA_Config()
{
}