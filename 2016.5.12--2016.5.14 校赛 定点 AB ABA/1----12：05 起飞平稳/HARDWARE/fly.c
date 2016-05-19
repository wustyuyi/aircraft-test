#include "fly.h"

void fly()
{
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
				USEHIGHT = 1;
				
				I_Lock = 1;
			}  
			break;
		case 12:
			if(stop == 2)
			{
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
			break;
		case 21:
			if(sen.high<25)
			{
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
		default:
			
			break;
	}
		
}
