#include "key.h"

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY0_Pin|KEY1_Pin|KEY2_Pin|KEY3_Pin|KEY4_Pin|KEY5_Pin;
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
	if(Read_KEY_3==RESET)
	{
		delay_ms(10);
		if(Read_KEY_3==RESET)
		{
			while(!Read_KEY_3);
			return 4;
		}	
	}
	if(Read_KEY_4==RESET)
	{
		delay_ms(10);
		if(Read_KEY_4==RESET)
		{
			while(!Read_KEY_4);
			return 5;
		}	
	}
	if(Read_KEY_5==RESET)
	{
		delay_ms(10);
		if(Read_KEY_5==RESET)
		{
			while(!Read_KEY_5);
			return 6;
		}	
	}
	return 0;
}



