#include "main.h"

u8 stop=0;
int i;
u8 flag = 0;
u16 flag1 = 0,flag2 = 0,flag5 = 0,flag10 = 0,flag20 = 0,flag50 = 0,flag100 = 0;
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
	//get_timer() = 76 ;
	
	
	I2cMaster_Init();
  //get_timer() = 76 ;
  mpu_dmp_init();
 	//get_timer() = 1621 ;
	GPIO_Config();
	//get_timer() = 1621 ;
	
	Filter_Init();
	
//	NRF_Usart_Pin_Init();//无线初始化
//	NRF_Read_Live_Init();//无线在线传输	
//  ReadData_Init();
	
	Scheduler_Init();
	
	
	
	//get_timer() = 1621 ;
	
	
	
  while(1)
	{
		//测试发送时间
//		for(i = 0;i<100 ; i++)
//		{
////			ANO_DT_Send_Status(sen.angle.roll,sen.angle.pitch,sen.angle.yaw,0,0,stop);   //1ms
////			ANO_DT_Send_Senser(sen.accel.x,sen.accel.y,sen.accel.z,sen.gyro.x,sen.gyro.y,sen.gyro.z,PID_Pitch.Pout_In,PID_Pitch.Iout_In,PID_Pitch.Dout_In,0); //2ms
////      ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//发送电机油门到匿名上位机   //2ms			

//		}
//		
//		OLED_ShowNum(0,2,Scheduler.cnt_1ms,8,16,1);
		
//		
////		while(1);
		if(flag != 10)
		{
			Scheduler_Loop();
		}
		else
		{
			OLED_ShowNum(0,2,get_timer(),5,16,1);
			OLED_ShowNum(48,2,flag1,5,16,1);
			OLED_ShowNum(0,4,flag2,5,16,1);
			OLED_ShowNum(48,4,flag5,5,16,1);
			OLED_ShowNum(0,6,flag10,5,16,1);
			OLED_ShowNum(48,6,flag20,5,16,1);
			while(1);
		}		  
	}
}
