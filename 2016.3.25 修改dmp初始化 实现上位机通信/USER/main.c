#include "main.h"

int main(void)
{
	u8 stop=0;
	SysTick_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	Struct_Init();
	

	MotoPwm_Init();
	OLED_Init();
	Key_Init();

	mpu_dmp_init();

	NRF_Usart_Pin_Init();//无线初始化
	NRF_Read_Live_Init();//无线在线传输
	
	ReadData_Init();

  while(1)
	{
			
		mpu_dmp_get_data(&angle.roll,&angle.pitch,&angle.yaw);		//dmp获取姿态角
		
		ANO_DT_Send_Status(angle.roll,-angle.pitch,-angle.yaw,0,0,0);  //串口1发送姿态角到匿名上位机
		
		if(Key_Scan()) 		//任意按键调整模式
		{
			stop = !stop;
			Stop();  
		}

		if(angle.roll>MaxAngle||angle.roll<MinAngle)		//最大角度限制
		{
			stop = 0;  //停止姿态调整
			Stop();		//关闭电机
		}
		
		if(stop)																		//姿态调整
			FlyControl_Out(&angle);
		
		ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//发送电机油门到匿名上位机
		
		NRF_UART_Connect();		//专用上位机数据传输
		
	}
}
