#include "scheduler.h"
u8 time = 0;
u32 Time = 0;
void Scheduler_Init()
{
	TIM_Int_Init(10-1,8400-1); //��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����10��Ϊ1ms     
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
		mpu_dmp_get_data();		//dmp��ȡ��̬��
		READ_MPU9250();
}

void Loop_200Hz() //5msִ��һ��
{
		ANO_DT_Send_Status(angle.roll,angle.pitch,angle.yaw,0,0,stop);  //����1������̬�ǵ�������λ��
		ANO_DT_Send_Senser(mag.x,mag.y,mag.z,Gyro.x,Gyro.y,Gyro.z,gyro.x,gyro.y,gyro.z,0);
		//		NRF_UART_Connect();		//ר����λ�����ݴ���
		if(stop)						//��̬����
		{
		  FlyControl_In(Gyro,angle);
		}
		ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//���͵�����ŵ�������λ��
}

void Loop_100Hz()  //10msִ��һ��
{
		if(Key_Scan()) 		//���ⰴ������ģʽ
		{
			stop = !stop; 
		}
		if(angle.roll>MaxAngle||angle.roll<MinAngle)		//���Ƕ�����
		{
			stop = 0;  //ֹͣ��̬����
		}	
		if(angle.pitch>MaxAngle||angle.pitch<MinAngle)		//���Ƕ�����
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
		OLED_ShowNum(0,0,Time,6,16,0);
	}
}
