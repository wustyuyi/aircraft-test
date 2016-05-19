#include "fly.h"

void fly()
{
	static uint32_t latm=0;
	unsigned long Timer;
	
	get_tick_count(&Timer);
	
	switch(FLYSTATE)
	{
		case 1:
			latm=Timer;
		  FLYSTATE = 10;
		  break;
		case 10:
			if(Timer-latm>=4000)				
			{
				Expect.roll = sen.angle.roll;
				Expect.pitch = sen.angle.pitch;
	//		  Expect.pitch = rc;
	//			Expect.roll = rc1;
				Expect.yaw = sen.angle.yaw;		//	锁定偏航
				
				FLYSTATE = 11;
			
			
				th1 = moto1_add;
				th2 = moto2_add;
				th3 = moto3_add;
				th4 = moto4_add;
			}		
		  break;
		case 11:  //起飞
			
			latm=Timer;
		  stop = 1;
			th1++;th2++;th3++;th4++;
		  if(sen.high > 6/*||abs(Expect.roll - sen.angle.roll)>1.0f||abs(Expect.pitch - sen.angle.pitch)>1.0f*/) //离地3cm
			{
				th1+= 20;th2+= 20;th3+= 20;th4+= 20;
				FLYSTATE = 12;
//				high0 = sen.high + 5;
				High = Expect.hight;
				
//				PID_Hight.LastAngle_Erro = High - high0;
				
				
				Expect.roll = 0;
				Expect.pitch = 0;
				
				
//				PID_Pitch.Iout_In = -4;
//				PID_Roll.Iout_In = -4;
				USEHIGHT = 1;
				
				I_Lock = 1;
			}  
			break;
		case 12:
			if(sen.high>=20)
			{
				DirCtrl(img.CerPtx,img.CerPty);
//				OPEN_POINT = 1;
			}
//			if(OPEN_POINT)//&&img.update)
//			{
////				img.update = 0;
//				
//			}
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
			if(sen.high>=Expect.hight - 10)
			{
				latm=Timer;
				FLYSTATE = 3;				
			}
			break;
		case 2:
			latm=Timer;
			High = -10;
		  if(th1>400)
			{	th1 -= 1;th2 -= 1;th3 -= 1;th4 -= 1;}	
			if(sen.high < 35)
			{
				FLYSTATE = 21;
			}
			if(FLYMODE==CTRLP)
				DirCtrl(img.CerPtx,img.CerPty);
			break;
		case 21:
			latm=Timer;
			if(sen.high<25)
			{
				OPEN_POINT = 0;
				roll0 = 0;
				pitch0 = 0;
				if(th1>50)
				{	th1 -= 50;th2 -= 50;th3 -= 50;th4 -= 50;}
					FLYSTATE = 22;				
			}
			break;
		case 22:
			if(sen.high<18)
			{
				Stop();
			}
		case 3:        //定点5s			
			if(Timer-latm>=6000)		//6s时间
			{
				latm=Timer;
				FLYSTATE = 2;
			}
		  if(stop == 2)
			{
				FLYSTATE = 2;
			}
			DirCtrl(img.CerPtx,img.CerPty);
		 break;
		default:
			
			break;
	}
		
}
