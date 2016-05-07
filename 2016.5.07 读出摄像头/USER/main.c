#include "main.h"

void SendPicPackage(void);

int main(void)
{
	uart_init(115200);
	SysTick_init();
	NRF_USART_Config();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	Key_Init();
	MotoPwm_Init();
	
	
	OV7620_Config();

	
	DCMI_Start();
	
  while(1)
	{
		if(DCMI_FINSH == 1)
		{
			DCMI_FINSH = 0;
			SendPicPackage();
			DCMI_Start();
		}
	}		
}
void SendPicPackage(void)
{
	uint16_t i,j;
	uint8_t bag[160];
	for(i=0;i<120;i++)
	{
		for(j=0;j<160;j++)
		{
			bag[j]=IMAGE[i*2][j*2];
		}
		SendHex(bag,160);
	}
	bag[0]=0xff;
	SendHex(bag,1);
}
