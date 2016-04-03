#include "main.h"
void Key_to_Pwm(void);
extern short A_X,A_Y,A_Z;
u8 t=0;
u16 x=0;
int g=0;
int accs[3]= {0,0,0},gyros[3]={0,0,0};
int main(void)
{
	 
	SysTick_init();
	uart_init(115200);
	Struct_Init();
//	NRF_USART_Config();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	Key_Init();
//	GY_GPIO_Config();
	g=mpu_dmp_init();
//	Init_MPU9250();
	MotoPwm_Init();
	OLED_ShowString(0,0,"CloseMoter");
	OLED_ShowString(0,4,"X:");
	OLED_ShowNum(16,4,x,3,16,0);
//	OLED_ShowString(0,2,"MPU offset...");
//	for(i=0;i<200;i++)
//	{
//		READ_MPU9250();
//		accs[0] += acc.x;
//		accs[1] += acc.y;
////		accs[2] += acc.z;
//		gyros[0] +=gyro.x;
//		gyros[1] +=gyro.y;
//		gyros[2] +=gyro.z;
//	}
//	offset_acc.x -= accs[0]/200;
//	offset_acc.y -= accs[1]/200;
////	offset_acc.z = accs[2]/200;
//	
//	offset_gyro.x -= gyros[0]/200;
//	offset_gyro.y -= gyros[1]/200;
//	offset_gyro.z -= gyros[2]/200;
//	OLED_ShowString(0,2,"MPU offset success");
	
  while(1)
	{
		if(mpu_dmp_get_data(&angle.roll,&angle.pitch,&angle.yaw)==0)
		{
			ANO_DT_Send_Status(angle.roll,-angle.pitch,-angle.yaw,0,0,0);
		}

		READ_MPU9250();
		
		ANO_DT_Send_Senser(acc.x,acc.y,acc.z,gyro.x,gyro.y,gyro.z,mag.x,mag.y,mag.z,0);
		
		Key_to_Pwm();
	}		
}


void Key_to_Pwm()
{

	switch(Key_Scan())
		{
			case 0 :break;
			case 1 :
				{
							t=!t;
							if(t)
							{
								OLED_ShowString(0,0,"OpenMoter");
								Moto_PwmUpdate(x,x,x,x);
							}
							else
							{
								OLED_ShowString(0,0,"CloseMoter");
								Moto_PwmUpdate(0,0,0,0);
							}
							break;
			  }
			case 2 :
				{
							x+=10;
							OLED_ShowNum(16,4,x,3,16,0);
							if(t)
							{
								Moto_PwmUpdate(x,x,x,x);
							}	
							break;
				}
		  case 3 :
				{
							x-=10;
							OLED_ShowNum(16,4,x,3,16,0);
							if(t)
							{
								Moto_PwmUpdate(x,x,x,x);
							}	
							break;
				}
			default : break;
		}
	
}


