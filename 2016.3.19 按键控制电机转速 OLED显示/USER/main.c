#include "main.h"


int main(void)
{
	u8 t=0;
	u16 x=0;
//	uart_init(115200);
	SysTick_init();
	NRF_USART_Config();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	Key_Init();
	MotoPwm_Init();
	
	OLED_ShowString(0,0,"CloseMoter");
	OLED_ShowString(0,4,"X:");
	OLED_ShowNum(16,4,x,3,16,0);
	
  while(1)
	{
		switch(Key_Scan())
		{
			case 0 :break;
			case 1 :
				{
							t=!t;
							if(t)
							{
								OLED_ShowString(0,0,"OpenMoter");
								Moto_PwmUpdate(x,x,x,x);
							}
							else
							{
								OLED_ShowString(0,0,"CloseMoter");
								Moto_PwmUpdate(0,0,0,0);
							}
							break;
			  }
			case 2 :
				{
							x+=10;
							OLED_ShowNum(16,4,x,3,16,0);
							if(t)
							{
								Moto_PwmUpdate(x,x,x,x);
							}	
							break;
				}
		  case 3 :
				{
							x-=10;
							OLED_ShowNum(16,4,x,3,16,0);
							if(t)
							{
								Moto_PwmUpdate(x,x,x,x);
							}	
							break;
				}
			default : break;
		}
	}		
}

