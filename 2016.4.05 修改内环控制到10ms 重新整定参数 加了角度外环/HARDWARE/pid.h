#ifndef __PID_H
#define __PID_H

#include "sys.h"
#include "struct.h"
#include "pwm.h"
#include "sen_data_build.h"
#include "ANO_DT.h"
#include "filter.h"

#define MaxAngle 40
#define MinAngle -40

typedef struct
{
	float Kp_O,Ki_O,Kd_O;
	float Kp_I,Ki_I,Kd_I;
	float Angle_Erro,LastAngle_Erro,Gyro_Erro,LastGyro_Erro,Target_Gyro;
	float Gyro_Diff,Gyro_Diff_Filter,Gyro_Diff_Filter_Ln2;
	float Target_rate;
	float Output,Pout_In,Iout_In,Dout_In,Pout_Out,Iout_Out,Dout_Out;
}pid;

extern pid PID_Pitch;
extern pid PID_Roll;
extern pid PID_Yaw;

void FlyControl_In(Vector3f _gyro,Angle _angle);
void Pid_Init(void);

#endif
