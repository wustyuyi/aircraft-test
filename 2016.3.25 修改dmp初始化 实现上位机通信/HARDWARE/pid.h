#ifndef __PID_H
#define __PID_H

#include "sys.h"
#include "struct.h"
#include "pwm.h"
#include "ANO_DT.h"


#define MaxAngle 45
#define MinAngle -45

typedef struct
{
	float Kp,Ki,Kd;
	float Integral;
	float Output;
}pid;


void FlyControl_Out(Angle *angle);

#endif
