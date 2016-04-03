#include "scheduler.h"

u8 time = 0;
u32 Time = 0;
void Scheduler_Init()
{
	TIM_Int_Init(10-1,18000-1); //��ʱ��ʱ��180M����Ƶϵ��18000������84M/8400=10Khz�ļ���Ƶ�ʣ�����10��Ϊ1ms     
	Scheduler.cnt_1ms = 0;
	Scheduler.cnt_2ms = 0;
	Scheduler.cnt_5ms = 0;
	Scheduler.cnt_10ms = 0;
	Scheduler.cnt_20ms = 0;
}

void Scheduler_IRQ() //1ms�ж� ��timer�����
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

void Loop_1000Hz()	//1msִ��һ��
{
		if(stop == 0)
		{
			Stop();		//�رյ��
		}
}

void Loop_500Hz()	//2msִ��һ��
{
	inv_mpu_read();
	
		if(stop)						//��̬����
		{
		  FlyControl_In(sen.gyro,sen.angle);
		}
}

void Loop_200Hz() //5msִ��һ��
{

		//		NRF_UART_Connect();		//ר����λ�����ݴ���	
	ANO_DT_Send_Status(sen.angle.roll,sen.angle.pitch,sen.angle.yaw,0,0,stop);
	ANO_DT_Send_Senser(sen.accel.x,sen.accel.y,sen.accel.z,sen.gyro.x,sen.gyro.y,sen.gyro.z,sen.compass_raw.x,sen.compass_raw.y,sen.compass_raw.z,0);
	
	ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//���͵�����ŵ�������λ��
}

void Loop_100Hz()  //10msִ��һ��
{
		if(Key_Scan()) 		//���ⰴ������ģʽ
		{
			stop = !stop; 
		}
		if(sen.angle.roll>MaxAngle||sen.angle.roll<MinAngle)		//���Ƕ�����
		{
			stop = 0;  //ֹͣ��̬����
		}	
		if(sen.angle.pitch>MaxAngle||sen.angle.pitch<MinAngle)		//���Ƕ�����
		{
			stop = 0;  //ֹͣ��̬����	
		}
}

void Loop_50Hz()	//20msִ��һ��
{
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
	}
}
