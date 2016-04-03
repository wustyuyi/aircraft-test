#include "scheduler.h"
u8 time = 0;
u32 Time = 0;
void Scheduler_Init()
{
	TIM_Int_Init(10-1,8400-1); //定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数10次为1ms     
	Scheduler.cnt_1ms = 0;
	Scheduler.cnt_2ms = 0;
	Scheduler.cnt_5ms = 0;
	Scheduler.cnt_10ms = 0;
	Scheduler.cnt_20ms = 0;
}

void Scheduler_IRQ() //1ms中断 在timer里调用
{
	Scheduler.cnt_1ms++;
	Scheduler.cnt_2ms++;
	Scheduler.cnt_5ms++;
	Scheduler.cnt_10ms++;
	Scheduler.cnt_20ms++;
}

void Scheduler_Loop()
{
	if(Scheduler.cnt_1ms >= 1){
		Loop_1000Hz();	
		Scheduler.cnt_1ms = 0;
	}
	if(Scheduler.cnt_2ms >= 2){
		Loop_500Hz();
		Scheduler.cnt_2ms = 0;
	}		
	if(Scheduler.cnt_5ms >= 5){	
		Loop_200Hz();
		Scheduler.cnt_5ms = 0;
	}
	if(Scheduler.cnt_10ms >= 10){		
		Loop_100Hz();
		Scheduler.cnt_10ms = 0;
	}
	if(Scheduler.cnt_20ms >= 20){		
		Loop_50Hz();
		Scheduler.cnt_20ms = 0;
	}
}

void Loop_1000Hz()	//1ms执行一次
{
		if(stop == 0)
		{
			Stop();		//关闭电机
		}
}

void Loop_500Hz()	//2ms执行一次
{
		mpu_dmp_get_data();		//dmp获取姿态角
		READ_MPU9250();
}

void Loop_200Hz() //5ms执行一次
{
		ANO_DT_Send_Status(angle.roll,angle.pitch,angle.yaw,0,0,stop);  //串口1发送姿态角到匿名上位机
		ANO_DT_Send_Senser(mag.x,mag.y,mag.z,Gyro.x,Gyro.y,Gyro.z,gyro.x,gyro.y,gyro.z,0);
		//		NRF_UART_Connect();		//专用上位机数据传输
		if(stop)						//姿态调整
		{
		  FlyControl_In(Gyro,angle);
		}
		ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//发送电机油门到匿名上位机
}

void Loop_100Hz()  //10ms执行一次
{
		if(Key_Scan()) 		//任意按键调整模式
		{
			stop = !stop; 
		}
		if(angle.roll>MaxAngle||angle.roll<MinAngle)		//最大角度限制
		{
			stop = 0;  //停止姿态调整
		}	
		if(angle.pitch>MaxAngle||angle.pitch<MinAngle)		//最大角度限制
		{
			stop = 0;  //停止姿态调整	
		}
}

void Loop_50Hz()	//20ms执行一次
{
	time++;
	if(time >= 50)
	{
		time = 0;
		Time++;
		OLED_ShowNum(0,0,Time,6,16,0);
	}
}
