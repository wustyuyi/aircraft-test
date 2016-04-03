#include "pid.h"

pid PID_Pitch;
pid PID_Roll;
pid PID_Yaw;

void FlyControl_Out(Angle *angle)
{

	Angle Control_angle;
	Angle Last_angle;
	
	PID_Pitch.Kp = 10;
	PID_Roll.Kp = 10;
	PID_Yaw.Kp = 10;
	
	Control_angle.pitch = angle->pitch;
	Control_angle.roll = angle->roll;
	Control_angle.yaw = angle->yaw;

	PID_Pitch.Output = PID_Pitch.Kp*Control_angle.pitch;
	PID_Roll.Output = PID_Roll.Kp*Control_angle.roll;
	PID_Yaw.Output = PID_Yaw.Kp*Control_angle.yaw;
	
	
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
	throttle1 = rc - PID_Roll.Output - PID_Yaw.Output;
	throttle2 = rc + PID_Pitch.Output + PID_Yaw.Output;
	throttle3 = rc + PID_Roll.Output - PID_Yaw.Output;
	throttle4 = rc - PID_Pitch.Output + PID_Yaw.Output;
	

//电机上下限幅
	if(throttle1 <= 0) throttle1 = 0;
	if(throttle2 <= 0) throttle2 = 0;
	if(throttle3 <= 0) throttle3 = 0;
	if(throttle4 <= 0) throttle4 = 0;

	if(throttle1 >= 500) throttle1 = 500;
	if(throttle2 >= 500) throttle2 = 500;
	if(throttle3 >= 500) throttle3 = 500;
	if(throttle4 >= 500) throttle4 = 500;
	
	
	Moto_PwmUpdate(throttle1,throttle2,throttle3,throttle4);	
}


