#include "pid.h"

pid PID_Pitch;
pid PID_Roll;
pid PID_Yaw;
extern int t;

void FlyControl_In(Vector3f _gyro,Angle _angle)
{
	
	PID_Pitch.Angle_Erro = _angle.pitch;
	
	PID_Pitch.Pout_Out = PID_Pitch.Kp_O * PID_Pitch.Angle_Erro;
	
//	PID_Pitch.Dout_Out = PID_Pitch.Kd_O * (PID_Pitch.Angle_Erro - PID_Pitch.LastAngle_Erro);
//		
//	PID_Pitch.LastAngle_Erro = PID_Pitch.Angle_Erro;
	
	PID_Pitch.Gyro_Erro = _gyro.y - PID_Pitch.Pout_Out + t;
	
	PID_Pitch.Pout_In = PID_Pitch.Kp_I * PID_Pitch.Gyro_Erro;
	
	PID_Pitch.Iout_In += PID_Pitch.Ki_I * PID_Pitch.Gyro_Erro / 500;
	//积分限幅
  PID_Pitch.Iout_In = _maxmin(PID_Pitch.Iout_In,100,-100);
	
	PID_Pitch.Dout_In = PID_Pitch.Kd_I * (PID_Pitch.Gyro_Erro - PID_Pitch.LastGyro_Erro);
	
	PID_Pitch.LastGyro_Erro = PID_Pitch.Gyro_Erro;
	
	PID_Pitch.Output = PID_Pitch.Pout_In + PID_Pitch.Iout_In + PID_Pitch.Dout_In;
	
//	PID_Pitch.Kp = 10;
//	PID_Roll.Kp = 10;
//	PID_Yaw.Kp = 10;
//	
//	Control_angle.pitch = angle->pitch;
//	Control_angle.roll = angle->roll;
//	Control_angle.yaw = angle->yaw;

//	PID_Pitch.Output = PID_Pitch.Kp*Control_angle.pitch;
//	PID_Roll.Output = PID_Roll.Kp*Control_angle.roll;
//	PID_Yaw.Output = PID_Yaw.Kp*Control_angle.yaw;
	
	
///////////////////////////////////////////////////////////////////
///////////////////////////	x型//////////////////////////////////////
///////////////////////////////////////////////////////////////////
//	throttle1 = rc - PID_Roll.Output + PID_Pitch.Output - PID_Yaw.Output;
//	throttle2 = rc - PID_Roll.Output - PID_Pitch.Output + PID_Yaw.Output;
//	throttle3 = rc + PID_Roll.Output + PID_Pitch.Output + PID_Yaw.Output;
//	throttle4 = rc + PID_Roll.Output - PID_Pitch.Output - PID_Yaw.Output;

///////////////////////////////////////////////////////////////////
///////////////////////////+型//////////////////////////////////////
///////////////////////////////////////////////////////////////////		
//	throttle1 = rc - PID_Roll.Output - PID_Yaw.Output;
	throttle2 = rc + PID_Pitch.Output + PID_Yaw.Output;
//	throttle3 = rc + PID_Roll.Output - PID_Yaw.Output;
	throttle4 = rc - PID_Pitch.Output + PID_Yaw.Output;
	

//电机上下限幅
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


void Pid_Init()
{
	PID_Pitch.Kp_I = 0;
	PID_Pitch.Ki_I = 0;
	PID_Pitch.Kd_I = 0;
	
	PID_Pitch.Kp_O = 0;
	PID_Pitch.Ki_O = 0;
	PID_Pitch.Kd_O = 0;
	
}


