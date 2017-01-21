/**
  ******************************************************************************
  * @file   
  * @author  wufulin
  * @version v1.0
  * @date    2015-11-03
  * @brief   key 应用函数库
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
  
  #include "key.h"
  #include "tool.h"
  
  /**
  * @brief  配置key用到的I/O
  * @param  无
  * @retval 无
  */
  void Key_GPIO_Config(void)
  {
	  GPIO_InitTypeDef GPIO_InitStructure;
	  
	  /* 开启按键端口PA0的时钟 */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	  
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
  }
 
  /**
  * @brief  检测是否有按键按下
  * @param  具体的端口和端口位
		@arg GPIOx: x可以是(A...G)
		@arg GPIO_Pin: 可以是GPIO_Pin_x (x可以是0...15)
  * @retval 按键的状态
		@arg KEY_ON: 按键按下
		@arg KEY_OFF: 按键没按下
  */
  uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
  {
	  if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON){
		  /* 延时消抖 */
		  Delay(1000);
		  if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON){
			  while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON); /* 等待按键释放 */
			  return KEY_ON;
		  }else{
			  return KEY_OFF;
		  }
	  }else{
		  return KEY_OFF;
	  }
  }
  