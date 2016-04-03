#include "key.h"

void Key_Init()
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = KEY0_Pin|KEY1_Pin|KEY2_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIO_Key,&GPIO_InitStructure);
	
}

u8 Key_Scan()
{
	if(Read_KEY_0==RESET)
	{
		delay_ms(10);
		if(Read_KEY_0==RESET)
		{
			while(!Read_KEY_0);
			return 1;
		}	
	}
	if(Read_KEY_1==RESET)
	{
		delay_ms(10);
		if(Read_KEY_1==RESET)
		{
			while(!Read_KEY_1);
			return 2;
		}	
	}
	if(Read_KEY_2==RESET)
	{
		delay_ms(10);
		if(Read_KEY_2==RESET)
		{
			while(!Read_KEY_2);
			return 3;
		}	
	}
	return 0;
}

