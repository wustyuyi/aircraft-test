#include "pid.h"

pid PID_Pitch;
pid PID_Roll;
pid PID_Yaw;

pid PID_Hight;



u8 high0=0;


float High_Rate;
float High_Rate_Raw;

CARMAN CM_HightRate={0,0,1.0,5.0,&High_Rate_Raw};
float velz=0; //期望速度
static uint8_t fistH=0;
void SetHight(void)
{	
	float avel;
	if(!USEHIGHT)
	{
		high0=0;
		fistH=1;
	}
	else
	{
		if(fistH)
		{
			fistH=0;
			high0=sen.high + 8;      //刚飞起时可能上升的高度会超过期望高度 所以加了8
			velz=High_Rate+1;
			PID_Hight.Angle_Erro=0;
			PID_Hight.LastAngle_Erro =high0 + 0.27 - sen.high;	//	防止初值为0 导致第一次测得实际速度特别大，形成积分后面飞机高度降下来
		}
		avel = (High-high0)/10;
		avel = _maxmin(avel,4,-4);
		if(velz+0.27f<avel)
			velz+=0.27f;
		else if(velz>avel+0.27f)
			velz-=0.27f;
		else
			velz=avel;
		high0+=velz;	
	}
}

//void Shigh()
//{
//	if(!USEHIGHT)
//	{
//		high0 = sen.high;
//	}
//	else
//	{
//		if((high0 <= sen.high)&&(high0+10<=High))
//		{
//			high0 +=10; 
//		}
//		else if((high0 >= sen.high)&&(high0-10>=High))
//		{
//			high0 -=10;
//		}
//		else
//		{
//			high0 = high0;
//		}
//	}	
//}

void FlyControl_Hight(int _hight)
{
	SetHight();
//	Shigh();
	
	PID_Hight.Angle_Erro = high0 - _hight ;
	
//	PID_Hight.Angle_Erro = Expect.hight - _hight ;
	
	PID_Hight.Angle_Erro = _maxmin(PID_Hight.Angle_Erro,38,-38);
	
	PID_Hight.Pout_Out = PID_Hight.Kp_O * PID_Hight.Angle_Erro;
	
	if(I_Lock)
	{
		PID_Hight.Iout_Out += PID_Hight.Ki_O * PID_Hight.Angle_Erro * 2 /25;
	
		PID_Hight.Iout_Out = _maxmin(PID_Hight.Iout_Out,10,-10);
	}
	else
	{
		PID_Hight.Iout_Out = 0;
	}
	
	
	PID_Hight.Dout_Out = PID_Hight.Kd_O * (PID_Hight.Angle_Erro - PID_Hight.LastAngle_Erro);

	PID_Hight.Target_rate = PID_Hight.Pout_Out + PID_Hight.Iout_Out + PID_Hight.Dout_Out;
			
	PID_Hight.Target_rate = _maxmin(PID_Hight.Target_rate,5,-5);
	
	High_Rate_Raw = PID_Hight.LastAngle_Erro - PID_Hight.Angle_Erro;
	
	High_Rate = CarManCulculate(&CM_HightRate);
	
	PID_Hight.LastAngle_Erro = PID_Hight.Angle_Erro;
	
	PID_Hight.Gyro_Erro = PID_Hight.Target_rate - High_Rate;
	
	PID_Hight.Pout_In = PID_Hight.Kp_I * PID_Hight.Gyro_Erro;
	
//	PID_Hight.Pout_In = _maxmin(PID_Hight.Pout_In,80,-80);
	
	if(I_Lock)
	{
		PID_Hight.Iout_In += PID_Hight.Ki_I * PID_Hight.Gyro_Erro * 2 /25;
		
		PID_Hight.Iout_In = _maxmin(PID_Hight.Iout_In,160,-80);
	}
	else
	{
		PID_Hight.Iout_In = 0;
	}

	PID_Hight.Gyro_Diff = PID_Hight.Gyro_Erro - PID_Hight.LastGyro_Erro;
		
	PID_Hight.Dout_In = PID_Hight.Kd_I * PID_Hight.Gyro_Diff;
	
	PID_Hight.LastGyro_Erro = PID_Hight.Gyro_Erro;
	
	PID_Hight.Output = PID_Hight.Pout_In + PID_Hight.Iout_In + PID_Hight.Dout_In;
	
	PID_Hight.Output =  _maxmin(PID_Hight.Output,200,-160);
}

void FlyControl_Yaw(float _gyro_z,float _angle_yaw)
{

	PID_Yaw.Angle_Erro = Expect.yaw - _angle_yaw ;
	
	if(PID_Yaw.Angle_Erro <= -180)
		PID_Yaw.Angle_Erro += 360;
	else if(PID_Yaw.Angle_Erro > 180)
		PID_Yaw.Angle_Erro -= 360;
	
	PID_Yaw.Pout_Out = PID_Yaw.Kp_O * PID_Yaw.Angle_Erro;
	
	if(I_Lock)
	{
		PID_Yaw.Iout_Out -= PID_Yaw.Ki_O * PID_Yaw.Angle_Erro/200;
	
		PID_Yaw.Iout_Out = _maxmin(PID_Yaw.Iout_Out,50,-50);
	}
	else
	{
		PID_Yaw.Iout_Out = 0;
	}

	
	PID_Yaw.Dout_Out = PID_Yaw.Kd_O * (PID_Yaw.Angle_Erro - PID_Yaw.LastAngle_Erro);
		
	PID_Yaw.LastAngle_Erro = PID_Yaw.Angle_Erro;
		
	PID_Yaw.Target_rate = PID_Yaw.Pout_Out + PID_Yaw.Iout_Out + PID_Yaw.Dout_Out;
	//外环输出限幅
	PID_Yaw.Target_rate = _maxmin(PID_Yaw.Target_rate,100,-100);
	
	PID_Yaw.Gyro_Erro = _gyro_z - PID_Yaw.Target_rate;
	
	PID_Yaw.Pout_In = PID_Yaw.Kp_I * PID_Yaw.Gyro_Erro;
	
	PID_Yaw.Pout_In = _maxmin(PID_Yaw.Pout_In,150,-150);
	
	if(I_Lock)
	{
		PID_Yaw.Iout_In += PID_Yaw.Ki_I * PID_Yaw.Gyro_Erro / 200;
			//积分限幅
		PID_Yaw.Iout_In = _maxmin(PID_Yaw.Iout_In,100,-100);
	}
	else
	{
		PID_Yaw.Iout_In = 0;
	}

	
	PID_Yaw.Gyro_Diff = PID_Yaw.Gyro_Erro - PID_Yaw.LastGyro_Erro;
	
//	LPF_1st_gyro(&PID_Yaw.Gyro_Diff_Filter,&PID_Yaw.Gyro_Diff,gyro_lpf);
	
//	PID_Pitch.Gyro_Diff_Filter_Ln2 = LPF_2nd_gyro(&Gyro_lpf_2nd,PID_Yaw.Gyro_Diff);
	
	PID_Yaw.Dout_In = PID_Yaw.Kd_I * PID_Yaw.Gyro_Diff;
	
	PID_Yaw.LastGyro_Erro = PID_Yaw.Gyro_Erro;
	
	PID_Yaw.Output = PID_Yaw.Pout_In + PID_Yaw.Iout_In + PID_Yaw.Dout_In;
}


void FlyControl_Pitch(float _gyro_y,float _angle_pitch)
{	
	PID_Pitch.Angle_Erro = Expect.pitch - _angle_pitch ;
	
	PID_Pitch.Pout_Out = PID_Pitch.Kp_O * PID_Pitch.Angle_Erro;
	
	if(I_Lock)
	{
		PID_Pitch.Iout_Out -= PID_Pitch.Ki_O * PID_Pitch.Angle_Erro/200;
	
	  PID_Pitch.Iout_Out = _maxmin(PID_Pitch.Iout_Out,50,-50);
	}
	else
	{
		PID_Pitch.Iout_Out = 0;
	}
	
	
	PID_Pitch.Dout_Out = PID_Pitch.Kd_O * (PID_Pitch.Angle_Erro - PID_Pitch.LastAngle_Erro);
		
	PID_Pitch.LastAngle_Erro = PID_Pitch.Angle_Erro;
		
	PID_Pitch.Target_rate = PID_Pitch.Pout_Out + PID_Pitch.Iout_Out + PID_Pitch.Dout_Out;
	//外环输出限幅
	PID_Pitch.Target_rate = _maxmin(PID_Pitch.Target_rate,100,-100);
	
	PID_Pitch.Gyro_Erro = _gyro_y - PID_Pitch.Target_rate;
	
	PID_Pitch.Pout_In = PID_Pitch.Kp_I * PID_Pitch.Gyro_Erro;
	
	PID_Pitch.Pout_In = _maxmin(PID_Pitch.Pout_In,150,-150);
	
	if(I_Lock)
	{
		PID_Pitch.Iout_In += PID_Pitch.Ki_I * PID_Pitch.Gyro_Erro / 200;
		//积分限幅
		PID_Pitch.Iout_In = _maxmin(PID_Pitch.Iout_In,100,-100);
	}
	else
	{
		PID_Pitch.Iout_In = 0;
	}
	
	
	PID_Pitch.Gyro_Diff = PID_Pitch.Gyro_Erro - PID_Pitch.LastGyro_Erro;
	
//	LPF_1st_gyro(&PID_Pitch.Gyro_Diff_Filter,&PID_Pitch.Gyro_Diff,gyro_lpf);
	
//	PID_Pitch.Gyro_Diff_Filter_Ln2 = LPF_2nd_gyro(&Gyro_lpf_2nd,PID_Pitch.Gyro_Diff);
	
	PID_Pitch.Dout_In = PID_Pitch.Kd_I * PID_Pitch.Gyro_Diff;
	
	PID_Pitch.LastGyro_Erro = PID_Pitch.Gyro_Erro;
	
	PID_Pitch.Output = PID_Pitch.Pout_In + PID_Pitch.Iout_In + PID_Pitch.Dout_In;
}


void FlyControl_Roll(float _gyro_x,float _angle_roll)
{	
	PID_Roll.Angle_Erro = Expect.roll - _angle_roll;
	
	PID_Roll.Pout_Out = PID_Roll.Kp_O * PID_Roll.Angle_Erro;
	
	if(I_Lock)
	{
		PID_Roll.Iout_Out -= PID_Roll.Ki_O * PID_Roll.Angle_Erro/200;
	
		PID_Roll.Iout_Out = _maxmin(PID_Roll.Iout_Out,50,-50);
	}
	else
	{
		PID_Roll.Iout_Out = 0;
	}

	
	PID_Roll.Dout_Out = PID_Roll.Kd_O * (PID_Roll.Angle_Erro - PID_Roll.LastAngle_Erro);
		
	PID_Roll.LastAngle_Erro = PID_Roll.Angle_Erro;
		
	PID_Roll.Target_rate = PID_Roll.Pout_Out + PID_Roll.Iout_Out + PID_Roll.Dout_Out;
	//外环输出限幅
	PID_Roll.Target_rate = _maxmin(PID_Roll.Target_rate,100,-100);
	
	PID_Roll.Gyro_Erro = _gyro_x - PID_Roll.Target_rate;
	
	PID_Roll.Pout_In = PID_Roll.Kp_I * PID_Roll.Gyro_Erro;
	
	PID_Roll.Pout_In = _maxmin(PID_Roll.Pout_In,150,-150);
	
	if(I_Lock)
	{
		PID_Roll.Iout_In += PID_Roll.Ki_I * PID_Roll.Gyro_Erro / 200;
		//积分限幅
		PID_Roll.Iout_In = _maxmin(PID_Roll.Iout_In,100,-100);
	}
	else
	{
		PID_Roll.Iout_In = 0;
	}

	
	PID_Roll.Gyro_Diff = PID_Roll.Gyro_Erro - PID_Roll.LastGyro_Erro;
	
//	LPF_1st_gyro(&PID_Roll.Gyro_Diff_Filter,&PID_Roll.Gyro_Diff,gyro_lpf);
	
//	PID_Pitch.Gyro_Diff_Filter_Ln2 = LPF_2nd_gyro(&Gyro_lpf_2nd,PID_Roll.Gyro_Diff);
	
	PID_Roll.Dout_In = PID_Roll.Kd_I * PID_Roll.Gyro_Diff;
	
	PID_Roll.LastGyro_Erro = PID_Roll.Gyro_Erro;
	
	PID_Roll.Output = PID_Roll.Pout_In + PID_Roll.Iout_In + PID_Roll.Dout_In;
}



void Pid_Init()
{
	
	PID_Pitch.Kp_I = 1.2;//1.5;
	PID_Pitch.Ki_I = 2;//0.4;
	PID_Pitch.Kd_I = 1.5;//3;
	PID_Pitch.Kp_O = 3;
	PID_Pitch.Ki_O = 0;
	PID_Pitch.Kd_O = 0;
	
	PID_Roll.Kp_I = 1.2;//1.5;
	PID_Roll.Ki_I = 2;//0.4;
	PID_Roll.Kd_I = 1.5;//3;
	PID_Roll.Kp_O = 3;
	PID_Roll.Ki_O = 0;
	PID_Roll.Kd_O = 0;
	
	PID_Yaw.Kp_I = 4.5;//1.2;//1.5;
	PID_Yaw.Ki_I = 0.5;//0;
	PID_Yaw.Kd_I = 2.0;//0.5;//0;
	PID_Yaw.Kp_O = 4.5;//2;//1.5;
	PID_Yaw.Ki_O = 0;
	PID_Yaw.Kd_O = 0;
	
	PID_Hight.Kp_I = 8;
	PID_Hight.Ki_I = 4;
	PID_Hight.Kd_I = 7;
	PID_Hight.Kp_O = 0.1;
	PID_Hight.Ki_O = 0.01;
	PID_Hight.Kd_O = 0;
	
}


void CONTROL()
{
	
	u16 moto1,moto2,moto3,moto4;
	
	FlyControl_Roll(sen.gyro.x,sen.angle.roll);
	FlyControl_Pitch(sen.gyro.y,sen.angle.pitch);
	FlyControl_Yaw(sen.gyro.z,sen.angle.yaw);
		
	moto1 = th1 - PID_Roll.Output - PID_Yaw.Output;
	moto2 = th2 + PID_Pitch.Output + PID_Yaw.Output;
	moto3 = th3 + PID_Roll.Output - PID_Yaw.Output;
	moto4 = th4 - PID_Pitch.Output + PID_Yaw.Output;
	
	if(USEHIGHT)
	{
		moto1 += PID_Hight.Output;
		moto2 += PID_Hight.Output;
		moto3 += PID_Hight.Output;
		moto4 += PID_Hight.Output;
	}
	
	if(stop == 0)
	{	
		USEHIGHT = 0;
		
		moto1 = 0;
		moto2 = 0;
		moto3 = 0;
		moto4 = 0;
		
		
		PID_Roll.Iout_In = 0;
		
		PID_Pitch.Iout_In = 0;
	}
	
	throttle1 = moto1;
	throttle2 = moto2;
	throttle3 = moto3;
	throttle4 = moto4;
	
	if(throttle1 <= 0) throttle1 = 0;
	if(throttle2 <= 0) throttle2 = 0;
	if(throttle3 <= 0) throttle3 = 0;
	if(throttle4 <= 0) throttle4 = 0;

	if(throttle1 >= 700) throttle1 = 700;
	if(throttle2 >= 700) throttle2 = 700;
	if(throttle3 >= 700) throttle3 = 700;
	if(throttle4 >= 700) throttle4 = 700;
		
	Moto_PwmUpdate(throttle1,throttle2,throttle3,throttle4);
}


void Stop()
{
	I_Lock = 0;
	stop = 0;
	USEHIGHT = 0;
	FLYMODE = 0;
	high0 = 0;
	th1 = 0;th2 = 0;th3 = 0;th4 = 0;
}


float CarManCulculate(CARMAN *pCarMan)
{
	float x_mid,p_mid,x_now,p_now,Kg;
	x_mid=pCarMan->x_last;                    //预测值为上一次的最优解
	p_mid=pCarMan->p_last+pCarMan->Q;	        //计算这一次均方差
	Kg=p_mid/(p_mid+pCarMan->R);		         	//计算卡尔曼增益
	x_now=x_mid+Kg*(*pCarMan->measure-x_mid);	//计算这一次最优解
	p_now=(1-Kg)*p_mid;		         						//更新均方误差
	pCarMan->p_last=p_now;			         			//保留数据给下一次用
	pCarMan->x_last=x_now;
	return x_now;
}



