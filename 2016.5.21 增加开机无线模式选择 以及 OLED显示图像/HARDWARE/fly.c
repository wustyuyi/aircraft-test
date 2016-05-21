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
			if(Timer-latm>=2000)				
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
		  if(FLYMODE==_A_B_||FLYMODE==A_B_A)
			{
				LineCtrlYaw();
				if(sen.high>Expect.hight-20)
				{
					if(_abs(dyaw)<20)
					{
						latm=Timer;
						FLYSTATE=4;
					}
				}
			}
			else if(FLYMODE==CTRLP)
			{
				if(sen.high>=Expect.hight - 10)
				{
					latm=Timer;
					FLYSTATE = 3;				
				}
			}
			
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
			DirCtrl(img.CerPtx,img.CerPty);
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
			if(FLYMODE==CTRLP||FLYMODE==_A_B_||FLYMODE==A_B_A)
			{
				DirCtrl(img.CerPtx,img.CerPty);
			}
			break;
		case 21:
			latm=Timer;
			if(sen.high<25)
			{
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
		case 4:				//	A_B_ 循迹 
//			if(img.CerR>20)  ////////////////
//			{
//				latm=Timer;
//				FLYSTATE=41;
//			}
			if(img.Line[0].pt1y>=50/*&&img.CerR>=15*/)	//	A->B 过中间圆
			{				
				latm=Timer;
				FLYSTATE = 43;
			}
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
		
			LineCtrl(img.Line[0],-35);

		break;
		case 41:
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
//			pitch0 = 1;
			if(img.Line[0].pt1y<=50)
			{
				latm=Timer;
				FLYSTATE = 42;
			}
		break;
		case 42:				//B点做出判断
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
//			if(get_timer()>latm+200)
//			{
				if(FLYMODE==_A_B_)
				{
					if(img.Line[0].pt1y>=40/*&&img.CerR>=15*/)
					{
						FLYSTATE = 43;
						latm=Timer;
					}
				}
				else if(FLYMODE==A_B_A)
				{
					if(img.Line[0].pt1y>=40&&img.CerR>=15)
					{
						FLYSTATE = 44;
						latm=Timer;
					}
				}			
//			}
			
			LineCtrl(img.Line[0],-35);
		break;
		case 43:			//	B点定点 准备降落
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
			if(get_timer()>latm+5000)
			{
				FLYSTATE = 2;
			}
			DirCtrl(img.CerPtx,img.CerPty);
		break;
		case 44:
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
			if(get_timer()>latm+2000)
			{
				FLYSTATE = 45;
				latm=Timer;
			}
			LineCtrl(img.Line[0],240);
//			DirCtrl(img.CerPtx,img.CerPty);
		break;
		case 45:	//ABA B点返回
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
			if(get_timer()>latm+2000)
			{
				if(img.Line[0].pt2y<=140&&img.CerR>=15)
				{
					FLYSTATE = 46;
				}
			}
			LineCtrl(img.Line[0],35);
		break;
		case 46:
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
			if(img.Line[0].pt2y>=190)
			{
				FLYSTATE = 47;
				latm=Timer;
			}
		break;
		case 47:		//	ABA B->A 过中间圆   
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
			if(get_timer()>latm+400)
			{
				if(img.Line[0].pt2y<=200&&img.CerR>=15)
				{
					FLYSTATE = 48;
					latm=Timer;
				}
			}	
			LineCtrl(img.Line[0],35);
		break;
		case 48:      //ABA A点准备降落
			if(stop == 2)
			{
				FLYSTATE = 2;
			}
			if(get_timer()>latm+5000)
			{
				FLYSTATE = 2;
			}
			DirCtrl(img.CerPtx,img.CerPty);
		break;
		default:
			
			break;
	}
		
}
