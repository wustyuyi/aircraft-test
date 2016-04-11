#include "pid.h"

pid PID_Pitch;
pid PID_Roll;
pid PID_Yaw;

u16 th1,th2,th3,th4;

void FlyControl_Pitch(float _gyro_y,float _angle_pitch)
{	
	PID_Pitch.Angle_Erro =  - _angle_pitch ;
	
	PID_Pitch.Pout_Out = PID_Pitch.Kp_O * PID_Pitch.Angle_Erro;
	
	PID_Pitch.Iout_Out -= PID_Pitch.Ki_O * PID_Pitch.Angle_Erro/100;
	
	PID_Pitch.Iout_Out = _maxmin(PID_Pitch.Iout_Out,50,-50);
	
	PID_Pitch.Dout_Out = PID_Pitch.Kd_O * (PID_Pitch.Angle_Erro - PID_Pitch.LastAngle_Erro);
		
	PID_Pitch.LastAngle_Erro = PID_Pitch.Angle_Erro;
		
	PID_Pitch.Target_rate = PID_Pitch.Pout_Out + PID_Pitch.Dout_Out;
	//外环输出限幅
	PID_Pitch.Target_rate = _maxmin(PID_Pitch.Target_rate,100,-100);
	
	PID_Pitch.Gyro_Erro = _gyro_y - PID_Pitch.Target_rate;
	
	PID_Pitch.Pout_In = PID_Pitch.Kp_I * PID_Pitch.Gyro_Erro;
	
	PID_Pitch.Pout_In = _maxmin(PID_Pitch.Pout_In,150,-150);
	
	PID_Pitch.Iout_In += PID_Pitch.Ki_I * PID_Pitch.Gyro_Erro / 100;
	//积分限幅
  PID_Pitch.Iout_In = _maxmin(PID_Pitch.Iout_In,100,-100);
	
	PID_Pitch.Gyro_Diff = PID_Pitch.Gyro_Erro - PID_Pitch.LastGyro_Erro;
	
//	LPF_1st_gyro(&PID_Pitch.Gyro_Diff_Filter,&PID_Pitch.Gyro_Diff,gyro_lpf);
	
//	PID_Pitch.Gyro_Diff_Filter_Ln2 = LPF_2nd_gyro(&Gyro_lpf_2nd,PID_Pitch.Gyro_Diff);
	
	PID_Pitch.Dout_In = PID_Pitch.Kd_I * PID_Pitch.Gyro_Diff;
	
	PID_Pitch.LastGyro_Erro = PID_Pitch.Gyro_Erro;
	
	PID_Pitch.Output = PID_Pitch.Pout_In + PID_Pitch.Iout_In + PID_Pitch.Dout_In;
}


void FlyControl_Roll(float _gyro_x,float _angle_roll)
{	
	PID_Roll.Angle_Erro =  - _angle_roll;
	
	PID_Roll.Pout_Out = PID_Roll.Kp_O * PID_Roll.Angle_Erro;
	
	PID_Roll.Iout_Out -= PID_Roll.Ki_O * PID_Roll.Angle_Erro/100;
	
	PID_Roll.Iout_Out = _maxmin(PID_Roll.Iout_Out,50,-50);
	
	PID_Roll.Dout_Out = PID_Roll.Kd_O * (PID_Roll.Angle_Erro - PID_Roll.LastAngle_Erro);
		
	PID_Roll.LastAngle_Erro = PID_Roll.Angle_Erro;
		
	PID_Roll.Target_rate = PID_Roll.Pout_Out + PID_Roll.Dout_Out;
	//外环输出限幅
	PID_Roll.Target_rate = _maxmin(PID_Roll.Target_rate,100,-100);
	
	PID_Roll.Gyro_Erro = _gyro_x - PID_Roll.Target_rate;
	
	PID_Roll.Pout_In = PID_Roll.Kp_I * PID_Roll.Gyro_Erro;
	
	PID_Roll.Pout_In = _maxmin(PID_Roll.Pout_In,150,-150);
	
	PID_Roll.Iout_In += PID_Roll.Ki_I * PID_Roll.Gyro_Erro / 100;
	//积分限幅
  PID_Roll.Iout_In = _maxmin(PID_Roll.Iout_In,100,-100);
	
	PID_Roll.Gyro_Diff = PID_Roll.Gyro_Erro - PID_Roll.LastGyro_Erro;
	
//	LPF_1st_gyro(&PID_Roll.Gyro_Diff_Filter,&PID_Roll.Gyro_Diff,gyro_lpf);
	
//	PID_Pitch.Gyro_Diff_Filter_Ln2 = LPF_2nd_gyro(&Gyro_lpf_2nd,PID_Roll.Gyro_Diff);
	
	PID_Roll.Dout_In = PID_Roll.Kd_I * PID_Roll.Gyro_Diff;
	
	PID_Roll.LastGyro_Erro = PID_Roll.Gyro_Erro;
	
	PID_Roll.Output = PID_Roll.Pout_In + PID_Roll.Iout_In + PID_Roll.Dout_In;
}



void Pid_Init()
{
	PID_Pitch.Kp_I = 1.5;
	PID_Pitch.Ki_I = 0.20;
	PID_Pitch.Kd_I = 3;
	
	PID_Pitch.Kp_O = 3;
	PID_Pitch.Ki_O = 0;
	PID_Pitch.Kd_O = 0;
	
	PID_Roll.Kp_I = 1.5;
	PID_Roll.Ki_I = 0.20;
	PID_Roll.Kd_I = 3;
	
	PID_Roll.Kp_O = 3;
	PID_Roll.Ki_O = 0;
	PID_Roll.Kd_O = 0;
	
}


void CONTROL()
{
	u16 moto1,moto2,moto3,moto4;
	FlyControl_Pitch(sen.gyro.y,sen.angle.pitch);
	FlyControl_Roll(sen.gyro.x,sen.angle.roll);
	
		
	moto1 = th1 - PID_Roll.Output - PID_Yaw.Output;
	moto2 = th2 + PID_Pitch.Output + PID_Yaw.Output;
	moto3 = th3 + PID_Roll.Output - PID_Yaw.Output;
	moto4 = th4 - PID_Pitch.Output + PID_Yaw.Output;
		

	if(stop == 0)
	{		
		PID_Pitch.Iout_Out = 0;
		PID_Pitch.Iout_In = 0;
		PID_Roll.Iout_Out = 0;
		PID_Roll.Iout_In = 0;
		
		moto1 = 0;
		moto2 = 0;
		moto3 = 0;
		moto4 = 0;
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
	stop = 0;
	PID_Pitch.Iout_Out = 0;
	PID_Pitch.Iout_In = 0;
	PID_Roll.Iout_Out = 0;
	PID_Roll.Iout_In = 0;
}
