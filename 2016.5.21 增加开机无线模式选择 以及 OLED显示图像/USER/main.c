#include "main.h"
u8 stop=0;

int main(void)
{
	u32 latm = 0;
	SysTick_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	

	Struct_Init();
	Pid_Init();
	
	MotoPwm_Init();
	PWM_IT_ENABLE();
	
	OLED_Init();
	Key_Init();
	//get_timer() = 76 ;
	OLED_ShowString(0,2,"comm_mode:?");
	latm = get_timer();
	while(1)
	{
		switch(Key_Scan())
		{
			case 1:
				wireless_mode = UART;
				OLED_ShowString(80,2,"UAR");
				goto Init;
			case 2:
				wireless_mode = NRF;
			  OLED_ShowString(80,2,"NRF");
				goto Init;
			default:
				if(get_timer()>latm+3000)
				{
					wireless_mode = UART;
				  OLED_ShowString(80,2,"UAR");
					goto Init;
				}
			break;
		}
	}
	
	Init:;
	
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
		
	//无线初始化
	if(wireless_mode == UART) 
	{
		uart_init(115200);
	}		
	else if(wireless_mode == NRF)
	{
		NRF_Usart_Pin_Init();//无线初始化
	  NRF_Read_Live_Init();//无线在线传输	
	}
	
	Scheduler_Init();	
	//get_timer() = 1621 ;
	
	OV7620_Config();	
	DCMI_Start();
		
  while(1)
	{
		Scheduler_Loop();
	}
} 
