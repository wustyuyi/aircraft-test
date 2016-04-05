#include "main.h"

u8 stop=0;

int main(void)
{
	SysTick_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	uart_init(115200);
	
	Struct_Init();
	Pid_Init();
	
	MotoPwm_Init();
	
	OLED_Init();
	Key_Init();
	
	I2cMaster_Init();
  mpu_dmp_init();	
	GPIO_Config();
	
	Filter_Init();
	
//	NRF_Usart_Pin_Init();//���߳�ʼ��
//	NRF_Read_Live_Init();//�������ߴ���	
//  ReadData_Init();
	
	Scheduler_Init();
	
  while(1)
	{
		Scheduler_Loop();
	}
}
