#include "scheduler.h"

extern int High_Rate;

u8 ti;
u8 time = 0;
u32 Time = 0;
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
	if(ti>=5)				//50ms
	{
		ti=0;
		Hight = Read_KS10X(SlaveAddress1,Hight);	//	��λcm		
		if(USEHIGHT)
			FlyControl_Hight(Hight);
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
	if(stop == 1)
	{
		th1 += 1;
		th2 += 1;
		th3 += 1;
		th4 += 1;		
		if(th1>=rc)
		{
			th1 = rc;
			th2 = rc;
			th3 = rc;
			th4 = rc;
			stop = 2;
		}	
	}
	else if(stop == 2)
	{
			th1 = rc;
			th2 = rc;
			th3 = rc;
			th4 = rc;
	}
	else if(stop == 3)
	{
		if(th1>100)
		{
			th1--;
			th2--;
			th3--;
			th4--;
		}
		else
		{
			th1=0;
			th2=0;
			th3=0;
			th4=0;
			stop = 0;
		}
	}
}

void Loop_50Hz()	//20msִ��һ��
{
	
}

void Loop_20Hz() //50msִ��һ��
{			
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
	ANO_DT_Send_Status(sen.angle.roll,sen.angle.pitch,sen.angle.yaw,Hight*100,0,stop);
	
	ANO_DT_Send_Senser(sen.accel.x,sen.accel.y,sen.accel.z,sen.gyro.x,sen.gyro.y,sen.gyro.z,Hight,High_Rate,0,0);

	ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//���͵�����ŵ�������λ��
}

void Loop_5Hz()	//200msִ��һ��
{
//	Hight = Read_KS10X(SlaveAddress1,Hight);	//	��λcm
	OLED_ShowNum(0,4,Hight,4,16,1);
	time++;
	if(time >= 5)
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
