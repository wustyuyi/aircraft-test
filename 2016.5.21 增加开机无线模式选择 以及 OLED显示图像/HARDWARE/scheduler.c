#include "scheduler.h"

extern float High_Rate;
extern float High_Rate_Raw;
extern float velz; //�����ٶ�

u8 ti;
u8 time = 0;
u32 Time = 0;
u8 t = 0;
int filter = 0,last = 0;
void Scheduler_Init()
{
	TIM_Int_Init(100-1,18000-1); //��ʱ��ʱ��180M����Ƶϵ��18000������84M/8400=10Khz�ļ���Ƶ�ʣ�����100��Ϊ10ms     
	Scheduler.cnt_10ms = 0;
	Scheduler.cnt_20ms = 0;
	Scheduler.cnt_50ms = 0;
	Scheduler.cnt_100ms = 0;
	Scheduler.cnt_200ms = 0;
}

void Scheduler_IRQ() //1ms�ж� ��timer�����
{
	Scheduler.cnt_10ms++;
	Scheduler.cnt_20ms++;
	Scheduler.cnt_50ms++;
	Scheduler.cnt_100ms++;
	Scheduler.cnt_200ms++;
	ti++;
	if(ti>=8)				//80ms
	{
		ti=0;
		
		last = filter;
		sen.high = Read_KS10X(SlaveAddress1,sen.high);	//	��λcm		
				//��ֹë��
		if((filter - sen.high>=20)||(filter - sen.high<=-20))
		{
			t++;
			if(t>=6)
			{
				t=0;
				filter = sen.high;
			}
			else
			{
				filter = last;
			}
		}
		else
		{
			t=0;
			filter = sen.high;
		}
		
		
//		if(USEHIGHT)
//			FlyControl_Hight(sen.high);
		FlyControl_Hight(filter);
	}	
}

void Scheduler_Loop()
{
	if(Scheduler.cnt_10ms >= 1){
		Loop_100Hz();	
		Scheduler.cnt_10ms = 0;
	}
	if(Scheduler.cnt_20ms >= 2){
		Loop_50Hz();
		Scheduler.cnt_20ms = 0;
	}		
	if(Scheduler.cnt_50ms >= 5){	
		Loop_20Hz();
		Scheduler.cnt_50ms = 0;
	}
	if(Scheduler.cnt_100ms >= 10){		
		Loop_10Hz();
		Scheduler.cnt_100ms = 0;
	}
	if(Scheduler.cnt_200ms >= 20){		
		Loop_5Hz();
		Scheduler.cnt_200ms = 0;
	}
}

void Loop_100Hz()	//10msִ��һ��
{	
	fly();
}

void Loop_50Hz()	//20msִ��һ��
{
	
}

void Loop_20Hz() //50msִ��һ��
{			
	CameraRun();
	
	if(sen.angle.roll>MaxAngle||sen.angle.roll<MinAngle)		//���Ƕ�����
	{
		Stop();  //ֹͣ��̬����
	}	
	if(sen.angle.pitch>MaxAngle||sen.angle.pitch<MinAngle)		//���Ƕ�����
	{
		Stop();  //ֹͣ��̬����	
	}
}

void Loop_10Hz()  //100msִ��һ��
{	 
	if(wireless_mode == UART)
	{
		ANO_DT_Send_Status(sen.angle.roll,sen.angle.pitch,sen.angle.yaw,sen.high*100,0,stop);
		
	//	ANO_DT_Send_Senser(sen.accel.x,sen.accel.y,sen.accel.z,sen.gyro.x,sen.gyro.y,sen.gyro.z,sen.high,High_Rate,High_Rate_Raw,0);
		ANO_DT_Send_Senser(img.Line[0].pt1x,img.Line[0].pt1y,img.Line[0].pt2x,img.Line[0].pt2y,img.CerPtx,img.CerPty,img.CerR,pitch0,filter,0);
		ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//���͵�����ŵ�������λ��
	}
	else if(wireless_mode == NRF)
	{
		NRF_UART_Connect();
	}
}

void Loop_5Hz()	//200msִ��һ��
{	
	time++;	
	if(FLYSTATE == 0)
	{
		menu_key();
		menu_Run();
	}
	if(time >= 5)
	{
		time = 0;
		Time++;
	}
}
