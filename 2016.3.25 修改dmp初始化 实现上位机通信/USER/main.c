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

	NRF_Usart_Pin_Init();//���߳�ʼ��
	NRF_Read_Live_Init();//�������ߴ���
	
	ReadData_Init();

  while(1)
	{
			
		mpu_dmp_get_data(&angle.roll,&angle.pitch,&angle.yaw);		//dmp��ȡ��̬��
		
		ANO_DT_Send_Status(angle.roll,-angle.pitch,-angle.yaw,0,0,0);  //����1������̬�ǵ�������λ��
		
		if(Key_Scan()) 		//���ⰴ������ģʽ
		{
			stop = !stop;
			Stop();  
		}

		if(angle.roll>MaxAngle||angle.roll<MinAngle)		//���Ƕ�����
		{
			stop = 0;  //ֹͣ��̬����
			Stop();		//�رյ��
		}
		
		if(stop)																		//��̬����
			FlyControl_Out(&angle);
		
		ANO_DT_Send_MotoPWM(throttle1,throttle2,throttle3,throttle4,0,0,0,0);		//���͵�����ŵ�������λ��
		
		NRF_UART_Connect();		//ר����λ�����ݴ���
		
	}
}
