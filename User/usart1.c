/**
  ******************************************************************************
  * @file   
  * @author  wufulin
  * @version v1.0
  * @date    2015-10-27
  * @brief   串口应用函数库
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
  #include "usart1.h"
  #include "stm32f10x.h"
  #include <stdio.h>
  
	uint8_t SendBuff[SENDBUFF_SIZE];
	
  /**
  * @brief  USART1 GPIO 配置，工作模式配置：115200 8-N-1
  * @param  无
  * @retval 无
  */
  void USART1_Config(void)
  {
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  
	  /* Config USART1 and GPIOA clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	  
	  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	  /* Configure USART1 Rx (PA.10) as input floating */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	  /* USART1 mode config */
	  USART_InitStructure.USART_BaudRate = 115200;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  USART_Init(USART1, &USART_InitStructure);
	  USART_Cmd(USART1, ENABLE); // 开启USART1外设
  }
  
  /**
  * @brief  USART1 TX DMA 配置，从内存到外设
  * @param  无
  * @retval 无
  */
	void USART1_DMA_Config()
	{
		DMA_InitTypeDef DMA_InitStructure;

		// 开启DMA时钟
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

		// 设置DMA源：串口数据寄存器地址
		DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(USART1->DR));

		// 内存地址
		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;

		// 从内存到外设
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;

		// 传输大小
		DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;

		// 外设地址不增
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

		// 内存地址自增
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

		// 外设数据单位
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

		// 内存数据单位
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

		// DMA模式
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;

		// 优先级:中
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

		// 禁止内存到内存的传输
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

		// 配置DMA1的4通道
		DMA_Init(DMA1_Channel4, &DMA_InitStructure);

		// 使能DMA
		DMA_Cmd(DMA1_Channel4, ENABLE);

	}

  /**
  * @brief  重定向c库函数printf到USART1
  * @param  
  * @retval 
  */
  int fputc(int ch, FILE *f)
  {
	  USART_SendData(USART1,(uint8_t) ch);
	  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
	  return (ch);
  }
  
  /**
  * @brief  重定向c库函数scanf到USART1
  * @param  
  * @retval
  */
  int fgetc(FILE *f)
  {
	  while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	  
	  return (int) USART_ReceiveData(USART1);
  }
  /*********************************************END OF FILE**********************/
