#include "fly.h"

extern u8 first;

void fly()
{
	static u32 tm = 0;
	if(get_timer()-tm >=10)
	{
		tm = get_timer();
		
		
	switch(FLYMODE)
	{
		case 1:
//			Expect.roll = sen.angle.roll;
//			Expect.pitch = sen.angle.pitch;
		  Expect.pitch = rc;
			Expect.roll = rc1;
			Expect.yaw = sen.angle.yaw;		//	Ëø¶¨Æ«º½
		  FLYMODE = 11;
		  break;
		case 11:  //Æð·É
			th1++;th2++;th3++;th4++;
		  if(sen.high > 6/*||abs(Expect.roll - sen.angle.roll)>1.0f||abs(Expect.pitch - sen.angle.pitch)>1.0f*/) //ÀëµØ3cm
			{
				th1+= 20;th2+= 20;th3+= 20;th4+= 20;
				FLYMODE = 12;
//				high0 = sen.high + 5;
				High = Expect.hight;
				
//				PID_Hight.LastAngle_Erro = High - high0;
				
				
				Expect.roll = 0;
				Expect.pitch = 0;
				
				
				PID_Pitch.Iout_In = -4;
				PID_Roll.Iout_In = -4;
				USEHIGHT = 1;
				
				I_Lock = 1;
			}  
			break;
		case 12:
			if(sen.high>=20)
			{
				OPEN_POINT = 1;
			}
			if(OPEN_POINT)//&&img.update)
			{
//				img.update = 0;
				DirCtrl(img.CerPtx,img.CerPty);
			}
			else if(OPEN_POINT == 0)
			{
				roll0 = 0;
				pitch0 = 0;
			}
			if(stop == 2)
			{
//				if((img.CerPtx == Expect.x)&&(img.CerPty == Expect.y))
					FLYMODE = 2;
			}		
			break;
		case 2:
			High = -10;
		  if(th1>400)
			{	th1 -= 1;th2 -= 1;th3 -= 1;th4 -= 1;}	
			if(sen.high < 35)
			{
				FLYMODE = 21;
			}
			if(OPEN_POINT)
			DirCtrl(img.CerPtx,img.CerPty);
			break;
		case 21:
			if(sen.high<25)
			{
				OPEN_POINT = 0;
				first = 1;
				roll0 = 0;
				pitch0 = 0;
				if(th1>50)
				{	th1 -= 50;th2 -= 50;th3 -= 50;th4 -= 50;}
					FLYMODE = 22;				
			}
			break;
		case 22:
			if(sen.high<8)
			{
				Stop();
			}
			break;
		case 3:
			
			LineCtrl(img.Line[0],-35);
			if(stop == 2)
			{
				FLYMODE = 2;
				roll0 = 0;
				pitch0 = 0;
			}			
			break;
		default:
			
			break;
	}
		
		
	}
	
		
}
