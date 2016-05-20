#include "jiguang.h"

void jiguang_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);	 //使能PD端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOD, &GPIO_InitStructure);	  //初始化GPIOD
	
//	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
}
void jiguang(u8 state)
{
	if(state == 0)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	}
	else if(state == 1)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_9);
	}
}