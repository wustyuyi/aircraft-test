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
	Scheduler.cnt_50ms = 0;
	Scheduler.cnt_100ms = 0;
}

void Scheduler_IRQ() //1ms�ж� ��timer�����
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

void Loop_1000Hz()	//1msִ��һ��
{

}

void Loop_500Hz()	//2msִ��һ��
{
	
}

void Loop_200Hz() //5msִ��һ��
{	
//	inv_mpu_read();
		//		NRF_UART_Connect();		//ר����λ�����ݴ���	
}

void Loop_100Hz()  //10msִ��һ��
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
void Loop_20Hz()  //50msִ��һ��
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
	ANO_DT_Send_Status(sen.angle.roll,sen.angle.pitch,sen.angle.yaw,0,0,stop);
	
	ANO_DT_Send_Senser(sen.accel.x,sen.accel.y,sen.accel.z,sen.gyro.x,sen.gyro.y,sen.gyro.z,0,0,0,0);

	ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//���͵�����ŵ�������λ��
}

