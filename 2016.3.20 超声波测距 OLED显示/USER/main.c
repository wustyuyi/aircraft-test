#include "main.h"


int main(void)
{
	u16 distance = 0,time = 0;
	SysTick_init();
	uart_init(115200);
//	NRF_USART_Config();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	Key_Init();
	
	MotoPwm_Init();
	OLED_ShowString(0,0,"CloseMoter");
	OLED_ShowString(0,2,"CSB Init ...");
	CSB_Init();
	OLED_ShowString(0,2,"CSB Init success");
	
	OLED_ShowNum(0,4,distance,4,16,0);
	OLED_ShowString(32,4,"mm");
	
  while(1)
	{
		distance = Read_KS10X(SlaveAddress1);
		OLED_ShowNum(0,4,distance,4,16,0);
		OLED_ShowNum(0,6,time++,4,16,0);
		printf("hello\r\n");
		delay_ms(500);
	}		
}

