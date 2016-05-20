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
	PWM_IT_ENABLE();
	
	OLED_Init();
	Key_Init();
	//get_timer() = 76 ;
	
	jiguang_Init();
	
	CSB_Init();
//	OLED_ShowString(0,2,"C Init success");
	
	I2cMaster_Init();
  //get_timer() = 76 ;
  mpu_dmp_init();
 	//get_timer() = 1621 ;
	GPIO_Config();
	//get_timer() = 1621 ;
	
	Filter_Init();
	
//	NRF_Usart_Pin_Init();//���߳�ʼ��
//	NRF_Read_Live_Init();//�������ߴ���	
//  ReadData_Init();
	
	
	Scheduler_Init();	
	//get_timer() = 1621 ;
	
	OV7620_Config();	
	DCMI_Start();
		
  while(1)
	{
		Scheduler_Loop();
	}
} 
