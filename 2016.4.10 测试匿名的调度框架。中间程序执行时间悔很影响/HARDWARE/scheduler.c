#include "scheduler.h"

extern u8 flag;
extern u16 flag1,flag2,flag5,flag10,flag20,flag50,flag100;
u8 time = 0;
u32 Time = 0;
void Scheduler_Init()
{
	TIM_Int_Init(10-1,18000-1); //定时器时钟180M，分频系数18000，所以84M/8400=10Khz的计数频率，计数10次为1ms     
	Scheduler.cnt_1ms = 0;
	Scheduler.cnt_2ms = 0;
	Scheduler.cnt_5ms = 0;
	Scheduler.cnt_10ms = 0;
	Scheduler.cnt_20ms = 0;
	Scheduler.cnt_50ms = 0;
	Scheduler.cnt_100ms = 0;
}

void Scheduler_IRQ() //1ms中断 在timer里调用
{
	Scheduler.cnt_1ms++;
	Scheduler.cnt_2ms++;
	Scheduler.cnt_5ms++;
	Scheduler.cnt_10ms++;
	Scheduler.cnt_20ms++;
	Scheduler.cnt_50ms++;
	Scheduler.cnt_100ms++;
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
	if(Scheduler.cnt_50ms >= 50){		
		Loop_20Hz();
		Scheduler.cnt_50ms = 0;
	}
	if(Scheduler.cnt_100ms >= 100){		
		Loop_10Hz();
		Scheduler.cnt_100ms = 0;
	}
}

void Loop_1000Hz()	//1ms执行一次
{
	flag1++;
}

void Loop_500Hz()	//2ms执行一次
{
	inv_mpu_read();
	flag2++;
}

void Loop_200Hz() //5ms执行一次
{
	flag5++;
	
		//		NRF_UART_Connect();		//专用上位机数据传输	
//	ANO_DT_Send_Status(sen.angle.roll,sen.angle.pitch,sen.angle.yaw,0,0,stop);
//	ANO_DT_Send_Senser(sen.accel.x,sen.accel.y,sen.accel.z,sen.gyro.x,sen.gyro.y,sen.gyro.z,PID_Pitch.Pout_In,PID_Pitch.Iout_In,PID_Pitch.Dout_In,0);

//	ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//发送电机油门到匿名上位机
}

void Loop_100Hz()  //10ms执行一次
{	
	  flag10++;
	
//		if(stop)						//姿态调整
//		{
		  FlyControl_In(sen.gyro,sen.angle);
//		}
		if(Key_Scan()) 		//任意按键调整模式
		{
			stop = !stop; 
		}
		if(sen.angle.roll>MaxAngle||sen.angle.roll<MinAngle)		//最大角度限制
		{
			stop = 0;  //停止姿态调整
		}	
		if(sen.angle.pitch>MaxAngle||sen.angle.pitch<MinAngle)		//最大角度限制
		{
			stop = 0;  //停止姿态调整	
		}
}

void Loop_50Hz()	//20ms执行一次
{
	flag20++;
	time++;
	if(time >= 50)
	{
		time = 0;
		Time++;
		
		OLED_ShowNum(0,0,Time/3600,2,16,0);
//		OLED_ShowString(16,0,":");
		OLED_ShowNum(24,0,Time%3600/60,2,16,0);
//		OLED_ShowString(40,0,":");
		OLED_ShowNum(48,0,Time%60,2,16,0);
		flag++; 
	}
}
void Loop_20Hz()  //50ms执行一次
{
	  flag50++;
		if(stop == 0)
		{
			Stop();		//关闭电机
		}
}

void Loop_10Hz()  //100ms执行一次
{
	flag100++;
	ANO_DT_Send_Status(sen.angle.roll,sen.angle.pitch,sen.angle.yaw,0,0,stop);
	
//	ANO_DT_Send_Senser(sen.accel.x,sen.accel.y,sen.accel.z,sen.gyro.x,sen.gyro.y,sen.gyro.z,PID_Pitch.Pout_In,PID_Pitch.Iout_In,PID_Pitch.Dout_In,0);

//	ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//发送电机油门到匿名上位机
}

